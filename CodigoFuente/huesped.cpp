#include "huesped.h"

Huesped::Huesped() : documento(""), antiguedad(0), puntuacion(0.0) {

    for (int i = 0; i < MAX_RSVXHPD; ++i) {
        reservaciones[i] = nullptr;
    }
}

Huesped::Huesped(string doc, unsigned int ant, float punt) : documento(doc), antiguedad(ant), puntuacion(punt) {

    for (int i = 0; i < MAX_RSVXHPD; ++i) {
        reservaciones[i] = nullptr;
    }
}

string Huesped::getDocumento() const { return documento; }
unsigned int Huesped::getAntiguedad() const { return antiguedad; }
float Huesped::getPuntuacion() const { return puntuacion; }
