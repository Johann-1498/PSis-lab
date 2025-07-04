#include "Banco.h"
#include "Boveda.h"
#include "Activos.h"
#include "SolicitudActivos.h"
#include "Transportador.h"
#include "Plaza.h"
#include <iostream>
#include <memory>

int main() {
    Banco banco("BANCO CENTRAL");

    auto activos1 = std::make_unique<Activos>();
    auto activos2 = std::make_unique<Activos>();
    auto activos3 = std::make_unique<Activos>();
    auto activos4 = std::make_unique<Activos>();

    banco.agregarBoveda("B1", activos1.get());
    banco.agregarBoveda("B2", activos2.get());
    banco.agregarBoveda("B3", activos3.get());
    banco.agregarBoveda("B4", activos4.get());

    SolicitudActivos sol1, sol2, sol3, sol4;
    sol1.dia = "01"; sol1.mes = "07"; sol1.tipo_op = TipoOperacion::DEPOSITO;
    sol2.dia = "01"; sol2.mes = "07"; sol2.tipo_op = TipoOperacion::RETIRO;
    sol3.dia = "02"; sol3.mes = "07"; sol3.tipo_op = TipoOperacion::DEPOSITO;
    sol4.dia = "02"; sol4.mes = "07"; sol4.tipo_op = TipoOperacion::RETIRO;

    sol1.detalle_billetes[CodigoActivo::SOLES] = {{"100", 2}};
    sol2.detalle_billetes[CodigoActivo::DOLARES] = {{"20", 1}};
    sol3.detalle_billetes[CodigoActivo::SOLES] = {{"50", 1}};
    sol4.detalle_billetes[CodigoActivo::BONO] = {{"1", 5}};

    Plaza plaza("LIMA");
    Boveda* b1 = banco.getBoveda("B1");
    Boveda* b2 = banco.getBoveda("B2");
    Boveda* b3 = banco.getBoveda("B3");
    Boveda* b4 = banco.getBoveda("B4");

    ParadaRuta pr1{b1, sol1};
    ParadaRuta pr2{b2, sol2};
    ParadaRuta pr3{b3, sol3};
    ParadaRuta pr4{b4, sol4};
    plaza.rutas = {pr1, pr2, pr3, pr4};

    Transportador transportador("Trans1", "T1");
    banco.iniciarTrasladoInterbancario(&transportador);

    auto regsDia = banco.consultarSaldosPorDia("01");
    std::cout << "Saldos para el día 01:\n";
    for (const auto& r : regsDia) {
        std::cout << "Boveda: " << r.boveda_afectada->getCodigo()
                  << " Monto: " << r.monto_total << std::endl;
    }
    auto regsMes = banco.consultarSaldosPorMes("07");
    std::cout << "Saldos para el mes 07:\n";
    for (const auto& r : regsMes) {
        std::cout << "Boveda: " << r.boveda_afectada->getCodigo()
                  << " Monto: " << r.monto_total << std::endl;
    }

    return 0;
}

