#pragma once
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <unordered_map>
#include <mutex>
#include "Usuario.h"
#include "Cancion.h"

class OptimizedReader {
public:
    // Reserva memoria para mapas antes de insertar
    static void reservarCapacidad(
        std::unordered_map<int, Usuario>& usuarios,
        std::unordered_map<int, Cancion>& canciones,
        size_t nUsuarios, size_t nCanciones)
    {
        usuarios.reserve(nUsuarios);
        canciones.reserve(nCanciones);
    }

    // Parser CSV usando mmap y procesamiento por bloques con hilos
    static void leerCSVConForkYHilos(
        const char* filename,
        std::unordered_map<int, Usuario>& usuarios,
        std::unordered_map<int, Cancion>& canciones,
        int numThreads,
        int pipe_fd[2]
    ) {
        // mmap del archivo
        int fd = open(filename, O_RDONLY);
        struct stat st; fstat(fd, &st);
        size_t fileSize = st.st_size;
        char* data = static_cast<char*>(mmap(NULL, fileSize, PROT_READ, MAP_PRIVATE, fd, 0));

        // Divide en trozos para cada hilo
        std::vector<std::thread> pool;
        size_t chunkSize = fileSize / numThreads;
        std::mutex mtx;

        for (int t = 0; t < numThreads; ++t) {
            size_t start = t * chunkSize;
            size_t end = (t == numThreads - 1) ? fileSize : (t + 1) * chunkSize;
            // Alinear líneas
            while (end < fileSize && data[end] != '\n') ++end;
            pool.emplace_back([&, start, end]() {
                std::vector<Registro> batch;
                batch.reserve(10000);
                size_t pos = start;
                while (pos < end) {
                    // parsear línea rápida: buscar comas y atoi/atof manual
                    char* lineStart = data + pos;
                    char* lineEnd = static_cast<char*>(memchr(lineStart, '\n', end - pos));
                    size_t len = lineEnd ? (lineEnd - lineStart) : (end - pos);

                    Registro reg = fastParseRegistro(lineStart, len);
                    batch.push_back(reg);

                    if (batch.size() >= 10000) {
                        procesarBatch(batch, usuarios, canciones, mtx);
                        batch.clear();
                    }
                    pos += len + 1;
                }
                if (!batch.empty()) procesarBatch(batch, usuarios, canciones, mtx);
            });
        }

        // Sigue usando fork y pipe
        pid_t pid = fork();
        if (pid == 0) {
            // Hijo: envía señal de lista al padre
            close(pipe_fd[0]);
            write(pipe_fd[1], "DONE", 4);
            _exit(0);
        }

        // Padre: espera señal
        close(pipe_fd[1]);
        char buf[4]; read(pipe_fd[0], buf, 4);

        for (auto& th : pool) th.join();
        munmap(data, fileSize);
        close(fd);
    }

private:
    struct Registro { int usuarioID; int cancionID; double calif; };

    static Registro fastParseRegistro(const char* ptr, size_t len) {
        // parse "uID,cID,calif"
        Registro r;
        const char* p = ptr;
        r.usuarioID = atoi(p);
        p = strchr(p, ',') + 1;
        r.cancionID = atoi(p);
        p = strchr(p, ',') + 1;
        r.calif = atof(p);
        return r;
    }

    static void procesarBatch(
        const std::vector<Registro>& batch,
        std::unordered_map<int, Usuario>& usuarios,
        std::unordered_map<int, Cancion>& canciones,
        std::mutex& mtx
    ) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& reg : batch) {
            // Bitset interno para Usuario: marca canción escuchada
            auto& u = usuarios[reg.usuarioID];
            u.escuchadas[reg.cancionID] = 1;
            auto& c = canciones[reg.cancionID];
            c.sumaCalificaciones += reg.calif;
        }
    }
};
