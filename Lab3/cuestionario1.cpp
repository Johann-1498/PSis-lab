#include <iostream>
using namespace std;

class Base {
    friend void mostrarDatos(Base& b); // función amiga
private:
    int secreto = 42;
};

void mostrarDatos(Base& b) {
    cout << "Accediendo al secreto: " << b.secreto << endl;
}

// Herencia simple
class Animal {
public:
    void hablar() { cout << "Animal hace sonido\n"; }
};

class Perro : public Animal {
public:
    void ladrar() { cout << "Guau!\n"; }
};

// Herencia múltiple
class A {
public:
    void mensajeA() { cout << "Clase A\n"; }
};

class B {
public:
    void mensajeB() { cout << "Clase B\n"; }
};

class C : public A, public B {
public:
    void mensajeC() { cout << "Clase C\n"; }
};

int main() {
    Base b;
    mostrarDatos(b);

    Perro p;
    p.hablar();
    p.ladrar();

    C obj;
    obj.mensajeA();
    obj.mensajeB();
    obj.mensajeC();

    return 0;
}
