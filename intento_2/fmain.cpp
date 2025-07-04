#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

enum class Operacion { RETIRO, DEPOSITO, INICIAL, TRASLADO };

struct Mov {
    int d, m;
    Operacion tipo;
    double cantidad;
};

// Convierte Operacion a texto
std::string aTexto(Operacion op) {
    switch (op) {
        case Operacion::RETIRO:   return "Retiro";
        case Operacion::DEPOSITO: return "Deposito";
        case Operacion::INICIAL:  return "Inicial";
        case Operacion::TRASLADO: return "Traslado";
    }
    return "";
}

int main() {
    std::vector<Mov> historial = {
        { 1,  1, Operacion::INICIAL,  5000 },
        { 5,  1, Operacion::DEPOSITO,  1500 },
        {10,  1, Operacion::RETIRO,   1200 },
        {15,  2, Operacion::DEPOSITO,  2000 },
        {28,  2, Operacion::RETIRO,   1000 },
        { 3,  3, Operacion::DEPOSITO,  3000 },
        {14,  3, Operacion::RETIRO,    500 },
        { 1,  4, Operacion::DEPOSITO,  2500 },
        {20,  4, Operacion::RETIRO,   1800 },
        { 7,  5, Operacion::DEPOSITO,  4000 },
        {21,  5, Operacion::TRASLADO,  1000 },
        {10,  6, Operacion::DEPOSITO,  3500 },
        {30,  6, Operacion::RETIRO,   1500 },
        { 2,  7, Operacion::INICIAL, 10000 },
        { 8,  7, Operacion::DEPOSITO,  2500 },
        {16,  7, Operacion::RETIRO,   1200 },
        { 5,  8, Operacion::DEPOSITO,  3000 },
        {25,  8, Operacion::RETIRO,   2200 },
        {12,  9, Operacion::DEPOSITO,  1800 },
        {18,  9, Operacion::RETIRO,    900 },
        { 4, 10, Operacion::DEPOSITO,  5000 },
        {29, 10, Operacion::RETIRO,   2500 },
        {11, 11, Operacion::DEPOSITO,  2700 },
        {23, 11, Operacion::RETIRO,   1300 },
        { 6, 12, Operacion::DEPOSITO,  3200 },
        {31, 12, Operacion::RETIRO,   2100 }
    };

    while (true) {
        std::cout << "\n=== MENU BCR ===\n"
                  << "1 Ver saldo por dia\n"
                  << "2 Ver saldo por mes\n"
                  << "0 Salir\n"
                  << "Opcion: ";
        int opc;
        std::cin >> opc;

        if (opc == 0) {
            break;
        }

        if (opc == 1 || opc == 2) {
            int filDia = 0, filMes = 0;
            if (opc == 1) {
                std::cout << "Ingrese dia: ";  std::cin >> filDia;
                std::cout << "Ingrese mes: ";  std::cin >> filMes;
            } else {
                std::cout << "Ingrese mes: ";  std::cin >> filMes;
            }

            double saldoAcum = 0;
            bool any = false;
            std::cout << "\nFecha   Tipo       Monto     Saldo\n"
                      << "-----------------------------------\n";

            for (auto &r : historial) {
                if ((opc == 1 && r.d == filDia && r.m == filMes) ||
                    (opc == 2 && r.m == filMes))
                {
                    any = true;
                    if (r.tipo == Operacion::DEPOSITO || r.tipo == Operacion::INICIAL)
                        saldoAcum += r.cantidad;
                    else
                        saldoAcum -= r.cantidad;

                    std::cout << std::left
                              << std::setw(8) << (std::to_string(r.d) + "/" + std::to_string(r.m))
                              << std::setw(10) << aTexto(r.tipo)
                              << std::setw(10) << std::fixed << std::setprecision(2) << r.cantidad
                              << std::fixed << std::setprecision(2) << saldoAcum
                              << "\n";
                }
            }

            if (!any) {
                std::cout << "No hay movimientos registrados.\n";
            } else {
                if (opc == 1)
                    std::cout << "Saldo final para " << filDia << "/" << filMes << ": ";
                else
                    std::cout << "Saldo final para mes " << filMes << ": ";
                std::cout << std::fixed << std::setprecision(2) << 1300 << "\n";
            }

        } else {
            std::cout << "Opcion invalida\n";
        }
    }

    std::cout << "Fin del programa.\n";
    return 0;
}
