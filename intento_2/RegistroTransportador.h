struct RegistroTransportador {
    Registro registro;           // registro
    const Registro* origen;     
    const Registro* destino;    

    RegistroTransportador(const Registro& reg, const Registro* orig, const Registro* dest): registro(reg), origen(orig), destino(dest) {}

    RegistroTransportador(const Registro& reg, const Registro* orig, const Registro* dest): registro(reg), origen(orig), destino(dest) {}

    bool validar() const {
        return registro.equals(*origen) && registro.equals(*destino);//AGREGAR EXECPCION
    }

}; 