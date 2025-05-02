class Tanque {
private:
    double contenido;

public:
//Se define la capacidad del tanque como 5000 la cual no se puede modificar
    static const int capacidad = 5000;
    //Constructor
    Tanque(){
        contenido = 0.0;
    }
    //Metodos
    double getContenido() const;
    void agregar(double cantidad);
    void sacar(double cantidad);
    void sacaMitad();
};
