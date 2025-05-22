#include "anfitrion.h"

Anfitrion::Anfitrion() {
    documento = 0;
    antiguedad = 0;
    puntuacion = 0;

}

Anfitrion::Anfitrion(unsigned int doc, unsigned int ant, float punt) {
    documento = doc;
    antiguedad = ant;
    puntuacion = punt;

}

unsigned int Anfitrion::getDocumento() const { return documento; }
unsigned int Anfitrion::getAntiguedad() const { return antiguedad; }
float Anfitrion::getPuntuacion() const { return puntuacion; }


