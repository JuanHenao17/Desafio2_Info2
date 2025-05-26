#include "anfitrion.h"

Anfitrion::Anfitrion(): documento(""), antiguedad(0), puntuacion(0.0) {

    for (int i = 0; i < MAX_ALOJXANF; ++i) {
        alojamientos[i] = nullptr;
    }
}

Anfitrion::Anfitrion(const string doc, unsigned int ant, float punt): documento(doc), antiguedad(ant), puntuacion(punt) {

    for (int i = 0; i < MAX_ALOJXANF; ++i) {
        alojamientos[i] = nullptr;
    }
}

string Anfitrion::getDocumento() const { return documento; }
unsigned int Anfitrion::getAntiguedad() const { return antiguedad; }
float Anfitrion::getPuntuacion() const { return puntuacion; }
