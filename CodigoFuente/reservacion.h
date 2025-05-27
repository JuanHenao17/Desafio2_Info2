#ifndef RESERVACION_H
#define RESERVACION_H
#include "fecha.h"
#include <string>
using namespace std;

class Reservacion {
private:
    unsigned int codigo;
    unsigned int noches;
    unsigned int codigoAlojamiento;
    string documentoHuesped;
    string metodoPago;      // PSE, TCrédito
    float monto;
    string nota;          // hasta 1000 caracteres

    Fecha fechaInicio;
    Fecha fechaPago;
    Fecha fechaFin;

public:
    Reservacion();
    Reservacion(unsigned int cod, const Fecha& inicio, unsigned int noches,
                unsigned int codAloj, const string& docHuesp,
                const string& metodo, double monto, const Fecha& pago, const string& nota);

    // Getters
    unsigned int getCodigo() const;
    unsigned int getNoches() const;
    unsigned int getCodigoAlojamiento() const;
    string getDocumentoHuesped() const;
    const string getMetodoPago() const;
    double getMonto() const;
    const string getNota() const;
    const Fecha& getFechaInicio() const;
    const Fecha& getFechaPago() const;
    const Fecha& getFechaFin() const;
};

#endif
