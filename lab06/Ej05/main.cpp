#include <iostream>
#include "Agenda.h"

int main() {
    Agenda agenda;
    int opcion;
    std::string nombre, direccion, telefono, email;
    short dia, mes, anio;

    do {
        std::cout << "1. Agregar persona\n2. Ver nombres\n3. Ver datos de una persona\n4. Salir\nIngrese su opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1:
                std::cout << "Ingrese nombre: "; std::getline(std::cin, nombre);
                std::cout << "Ingrese direccion: "; std::getline(std::cin, direccion);
                std::cout << "Ingrese telefono: "; std::getline(std::cin, telefono);
                std::cout << "Ingrese email: "; std::getline(std::cin, email);
                std::cout << "Ingrese dia de nacimiento: "; std::cin >> dia;
                std::cout << "Ingrese mes de nacimiento: "; std::cin >> mes;
                std::cout << "Ingrese anio de nacimiento: "; std::cin >> anio;
                agenda.agregarPersona(Persona(nombre, direccion, telefono, email, dia, mes, anio));
                break;
            case 2:
                agenda.mostrarNombres();
                break;
            case 3:
                std::cout << "Ingrese nombre de la persona a buscar: ";
                std::cin.ignore();
                std::getline(std::cin, nombre);
                agenda.mostrarDatosPersona(nombre);
                break;
            case 4:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);

    return 0;
}
