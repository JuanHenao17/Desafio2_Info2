#include "reservacion.h"
#include <cstring>

Reservacion::Reservacion() {
    codigo = 0;
    noches = 0;
    codigoAlojamiento = 0;
    documentoHuesped = 0;
    metodoPago = "";
    monto = 0;
    nota = "";
}

Reservacion::Reservacion(unsigned int cod, unsigned int n,
                         unsigned int codAloj, unsigned int docHuesp,
                         const string metodo, double m, const string notita) {
    codigo = cod;
    noches = n;
    codigoAlojamiento = codAloj;
    documentoHuesped = docHuesp;
    metodoPago = metodo;
    monto = m;
    nota = notita; // Seguridad
}

unsigned int Reservacion::getCodigo() const { return codigo; }
unsigned int Reservacion::getNoches() const { return noches; }
unsigned int Reservacion::getCodigoAlojamiento() const { return codigoAlojamiento; }
unsigned int Reservacion::getDocumentoHuesped() const { return documentoHuesped; }
const string Reservacion::getMetodoPago() const { return metodoPago; }
double Reservacion::getMonto() const { return monto; }
const string Reservacion::getNota() const { return nota; }


