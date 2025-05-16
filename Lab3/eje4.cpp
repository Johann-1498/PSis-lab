#include <iostream>

int main() {
    int opcion = 0;
    do {
        std::cout << "\n--------Que genero de pelicula quieres ver?--------\n";
        std::cout << "1. Accion\n";
        std::cout << "2. Comedia\n";
        std::cout << "3. Drama\n";
        std::cout << "4. Ciencia ficcion\n";
        std::cout << "5. SALIR\n";
        std::cout << "Seleccione una opcion (1-5): ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "Has seleccionado: Accion\n";
                break;
            case 2:
                std::cout << "Has seleccionado: Comedia\n";
                break;
            case 3:
                std::cout << "Has seleccionado: Drama\n";
                break;
            case 4:
                std::cout << "Has seleccionado: Ciencia ficcion\n";
                break;
            case 5:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opcion no valida. Por favor ingresa un numero entre 1 y 5.\n";
        }
    } while (opcion != 5);

    return 0;
}
