#ifndef RESERVACION_H
#define RESERVACION_H

#include <string>
using namespace std;

class Reservacion {
private:
    int codigo;
    int noches;
    int codigoAlojamiento;
    int documentoHuesped;
    string metodoPago;      // PSE, TCrédito
    float monto;
    string nota;          // hasta 1000 caracteres

public:
    Reservacion();
    Reservacion(unsigned int cod, unsigned int noches,
                unsigned int codAloj, unsigned int docHuesp,
                const string metodo, double monto, const string nota);

    // Getters
    unsigned int getCodigo() const;
    unsigned int getNoches() const;
    unsigned int getCodigoAlojamiento() const;
    unsigned int getDocumentoHuesped() const;
    const string getMetodoPago() const;

    double getMonto() const;
    const string getNota() const;


};

#endif
