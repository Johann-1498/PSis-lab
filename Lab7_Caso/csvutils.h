#pragma once

#include <string>
#include <vector>
#include <fstream>

class CSVUtils {
public:
    static void crearDirectorioSiNoExiste(const std::string& ruta) {
        size_t pos = 0;
        std::string dir;
        
        while ((pos = ruta.find_first_of('/', pos + 1)) != std::string::npos) {
            dir = ruta.substr(0, pos);
            #ifdef _WIN32
                mkdir(dir.c_str());
            #else
                mkdir(dir.c_str(), 0777);
            #endif
            if (pos == std::string::npos) break;
        }
    }

    static bool archivoExiste(const std::string& nombreArchivo) {
        std::ifstream f(nombreArchivo.c_str());
        return f.good();
    }

    static std::vector<std::string> dividirLineaCSV(const std::string& linea) {
        std::vector<std::string> campos;
        std::string campo;
        bool entreComillas = false;
        
        for (char c : linea) {
            if (c == '"') {
                entreComillas = !entreComillas;
            } else if (c == ',' && !entreComillas) {
                campos.push_back(campo);
                campo.clear();
            } else {
                campo += c;
            }
        }
        campos.push_back(campo);
        return campos;
    }
};