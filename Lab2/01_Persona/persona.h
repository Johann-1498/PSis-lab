#include <iostream>
#include <string>  // Necesario para usar std::string
using namespace std;

class Persona {
    private:
        char nombre[50];

    public:
        void dormir();
        void hablar();
        void contar();
        void adquirirNombre();
        void decirNombre();
};
