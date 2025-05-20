#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring> // para medir la longitud de la palabra

using namespace std;

// funcion para mostrar la palabra con caracteres ya adivinados
void mostrarPalabra(const char* palabra, const vector<char>&
letrasAdivinadas, bool mostrarGuiones) {
    for (int i = 0; palabra[i] != '\0'; i++) {
        if (find(letrasAdivinadas.begin(), letrasAdivinadas.end(), palabra[i]) != letrasAdivinadas.end()) {
            cout << palabra[i];
        } else if (mostrarGuiones) {
            cout << "_";
        } else {
            cout << " ";
        }
    }
    cout << endl;
}

// funcion para verificar si la lestra esta en lapalabra
bool verificarLetra(const char* palabra, char letter) {
    for (int i = 0; palabra[i] != '\0'; i++) {
        if (palabra[i] == letter) {
            return true;
        }
    }
    return false;
}

// Funcion para verificar si todas las letras fueron adivinadas
bool palabraAdivinada(const char* palabra, const vector<char>& letrasAdivinadas) {
    for (int i = 0; palabra[i] != '\0'; i++) {
        if (find(letrasAdivinadas.begin(), letrasAdivinadas.end(),
        palabra[i]) == letrasAdivinadas.end()) {
            return false;
        }
    }
    return true;
}

int main() {
    // Obtenemos la palabra
    char palabra[50];
    cout << "Ingrese la palabra secreta: ";
    cin.getline(palabra, 50);

    // Inicializamos vidas
    int vidas = strlen(palabra)-1;
    vector<char> letrasAdivinadas;  

    // bucle del juego
    while (vidas > 0 && !palabraAdivinada(palabra, letrasAdivinadas)) {
        mostrarPalabra(palabra, letrasAdivinadas, true); //Mostrar palabracon guiones
        cout << "Adivina una letra: ";
        char guess;
        cin >> guess;
        guess = tolower(guess); // Convertir a minuscula
        // revisar si ya fue adivinada la letra
        if (find(letrasAdivinadas.begin(), letrasAdivinadas.end(), guess) != letrasAdivinadas.end()) {
            cout << "Ya has adivinado esa letra. Inténtalo de nuevo." << endl;
            continue;
        }
        // añadir la letra adivinada a la lista
        letrasAdivinadas.push_back(guess);
        // verificar si la letra esta en la palabra
        if (verificarLetra(palabra, guess)) {
            cout << "La letra '" << guess << "' esta en la palabra." <<
            endl;
        } else {
            vidas--;
            cout << "Mal, te quedan " << vidas << " vidas." << endl;
        }
    }
    // mostrarResultado
    mostrarPalabra(palabra, letrasAdivinadas, false);
    if (vidas > 0) {
        cout << "Adivinaste la palabra: " << palabra <<
        endl;
    } else {
        cout << "Perdiste. La palabra era: " << palabra <<
        endl;
    }
    return 0;
}
