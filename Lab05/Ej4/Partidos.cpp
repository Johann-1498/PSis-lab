#include <stdint.h>  // para tipos enteros de tamaño fijo
#include <stdbool.h> // para bool
#include <stddef.h>  // para size_t
#include <iostream>
#include <string>
use namespace std;
struct Equipo {
  std::string nombre;
  int victorias = 0, derrotas = 0;
  virtual ~Equipo() = default;               // para borrar correctamente
  virtual void print() const = 0;        // método abstracto
  virtual void crearEquipo(){

  }      

};

struct Baloncesto : Equipo {
  int perdidas = 0, rebotes = 0;
  std::string mejorAnotadorTriple;
  int triples = 0;
  void print() const override { /* … */ }
  virtual void crearEquipo(){}

};

struct Futbol : Equipo {
  int empates = 0, golFavor = 0;
  std::string goleador;
  int golesGol = 0;
  void print() const override { /* … */ }
  virtual void crearEquipo(){}

};


#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>  // std::numeric_limits

// Clase base abstracta
struct Equipo {
    std::string nombre;
    int victorias = 0;
    int derrotas  = 0;
    virtual ~Equipo() = default;
    virtual void print() const = 0;
};

// Baloncesto
struct Baloncesto : Equipo {
    int perdidas               = 0;
    int rebotes                = 0;
    std::string mejorTriplero;
    int triples                = 0;

    // Factory para crear e inicializar
    static std::unique_ptr<Equipo> crear() {
        auto p = std::make_unique<Baloncesto>();
        std::cout << "\n--- Nuevo equipo de BALONCESTO ---\n";
        std::cout << "Nombre: ";
        std::getline(std::cin, p->nombre);
        std::cout << "Victorias: "; std::cin >> p->victorias;
        std::cout << "Derrotas:   "; std::cin >> p->derrotas;
        std::cout << "Pérdidas de balón: "; std::cin >> p->perdidas;
        std::cout << "Rebotes:           "; std::cin >> p->rebotes;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Mejor triplero:    "; std::getline(std::cin, p->mejorTriplero);
        std::cout << "Triples anotados:  "; std::cin >> p->triples;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return p;
    }

    void print() const override {
        std::cout
            << "BALONCESTO — " << nombre << "\n"
            << "  Vict: " << victorias << "  Der: " << derrotas << "\n"
            << "  Pérdidas: " << perdidas << "  Rebotes: " << rebotes << "\n"
            << "  Triplero: " << mejorTriplero
            << " (" << triples << " triples)\n";
    }
};

// Fútbol
struct Futbol : Equipo {
    int empates    = 0;
    int golFavor   = 0;
    std::string goleador;
    int golesGole  = 0;

    static std::unique_ptr<Equipo> crear() {
        auto p = std::make_unique<Futbol>();
        std::cout << "\n--- Nuevo equipo de FÚTBOL ---\n";
        std::cout << "Nombre: ";
        std::getline(std::cin, p->nombre);
        std::cout << "Victorias: "; std::cin >> p->victorias;
        std::cout << "Derrotas:   "; std::cin >> p->derrotas;
        std::cout << "Empates:    "; std::cin >> p->empates;
        std::cout << "Goles a favor: "; std::cin >> p->golFavor;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Goleador:   "; std::getline(std::cin, p->goleador);
        std::cout << "Goles del goleador: "; std::cin >> p->golesGole;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return p;
    }

    void print() const override {
        std::cout
            << "FÚTBOL — " << nombre << "\n"
            << "  Vict: " << victorias << "  Der: " << derrotas
            << "  Emp: " << empates << "\n"
            << "  Goles favor: " << golFavor << "\n"
            << "  Goleador: " << goleador
            << " (" << golesGole << " goles)\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Equipo>> liga;
    int n;

    std::cout << "¿Cuántos equipos de baloncesto quieres ingresar? ";
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < n; ++i)
        liga.push_back(Baloncesto::crear());

    std::cout << "\n¿Cuántos equipos de fútbol quieres ingresar? ";
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < n; ++i)
        liga.push_back(Futbol::crear());

    std::cout << "\n======= Resumen de todos los equipos =======\n";
    for (const auto& equipo : liga) {
        equipo->print();
        std::cout << "-------------------------------------------\n";
    }

    return 0;
}
