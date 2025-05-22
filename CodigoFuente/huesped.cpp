#include "huesped.h"

Huesped::Huesped() {
    documento = 0;
    antiguedad = 0;
    puntuacion = 0;

}

Huesped::Huesped(unsigned int doc, unsigned int ant, float punt) {
    documento = doc;
    antiguedad = ant;
    puntuacion = punt;

}

unsigned int Huesped::getDocumento() const { return documento; }
unsigned int Huesped::getAntiguedad() const { return antiguedad; }
float Huesped::getPuntuacion() const { return puntuacion; }


