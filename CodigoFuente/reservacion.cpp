#include "reservacion.h"
#include <string>

Reservacion::Reservacion() : codigo(0), noches(0), codigoAlojamiento(0), documentoHuesped(""), metodoPago(""),
    monto(0.0), nota("") {

}


Reservacion::Reservacion(unsigned int cod, const Fecha& inicio, unsigned int n,
                         unsigned int codAloj, const string& docHuesp,
                         const string& metodo, double m, const Fecha& pago, const string& notita) : codigo(cod), noches(n),
    codigoAlojamiento(codAloj), documentoHuesped(docHuesp), metodoPago(metodo), monto(m), nota(notita) {

    fechaInicio = inicio;
    fechaPago = pago;
    fechaFin = fechaInicio.sumarDias(noches);

}

unsigned int Reservacion::getCodigo() const { return codigo; }
unsigned int Reservacion::getNoches() const { return noches; }
unsigned int Reservacion::getCodigoAlojamiento() const { return codigoAlojamiento; }
string Reservacion::getDocumentoHuesped() const { return documentoHuesped; }
const string Reservacion::getMetodoPago() const { return metodoPago; }
double Reservacion::getMonto() const { return monto; }
const string Reservacion::getNota() const { return nota; }
const Fecha& Reservacion::getFechaInicio() const { return fechaInicio; }
const Fecha& Reservacion::getFechaPago() const { return fechaPago; }
const Fecha& Reservacion::getFechaFin() const { return fechaFin; }
