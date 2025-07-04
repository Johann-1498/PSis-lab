#include <iostream>
#include <csignal>
#include <cstdlib>


using namespace std;


// Manejador de la señal SIGABRT
void signalHandler(int signum) {
   cout << "Hola, recibí la señal " << signum << endl;
   // Termina el programa después de manejar la señal
   exit(signum);
}


int main() {
   // Registrar el manejador de la señal SIGABRT
   signal(SIGABRT, signalHandler);


   cout << "Presiona Enter para generar SIGABRT..." << endl;
   cin.get();


   // Generar la señal SIGABRT
   raise(SIGABRT);


   // Este código no se ejecutará debido a la terminación del programa en el manejador de señales
   cout << "Este mensaje no se imprimirá." << endl;


   return 0;
}
