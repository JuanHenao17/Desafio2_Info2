#include "alojamiento.h"
#include <iostream>
#include <string>

Alojamiento::Alojamiento() : codigo(0), nombre(""), tipo(""), direccion(""), municipio(""), departamento(""), precioNoche(0.0) {

    for (int i = 0; i < 6; i++) {
        amenidades[i] = false;
    }

    for (int i = 0; i < MAX_RSVXALOJ; ++i) {
        reservaciones[i] = nullptr;
    }
}


Alojamiento::Alojamiento(unsigned int cod, const string nom, const string tip, const string dir,
                         const string muni, const string depto, double precio, const bool amen[]) : codigo(cod), nombre(nom), tipo(tip),
    direccion(dir), municipio(muni), departamento(depto), precioNoche(precio) {

    for (int i = 0; i < 6; i++) {
        amenidades[i] = amen[i];
    }

    for (int i = 0; i < MAX_RSVXALOJ; ++i) {
        reservaciones[i] = nullptr;
    }
}

unsigned int Alojamiento::getCodigo() const { return codigo; }
const string Alojamiento::getNombre() const { return nombre; }
const string Alojamiento::getTipo() const { return tipo; }
const string Alojamiento::getDireccion() const { return direccion; }
const string Alojamiento::getMunicipio() const { return municipio; }
const string Alojamiento::getDepartamento() const { return departamento; }
double Alojamiento::getPrecioNoche() const { return precioNoche; }
bool* Alojamiento::getAmenidades() { return amenidades; }

void Alojamiento::agregarReservacion(Reservacion* r, unsigned int& iteraciones) {
    for (int i = 0; i < MAX_RSVXALOJ; i++) {
        iteraciones++;
        if (reservaciones[i] == nullptr) {
            reservaciones[i] = r;
            return;
        }
    }
    cout << "Alojamiento con codigo " << codigo << " ya tiene el maximo de reservas." << endl;
}
