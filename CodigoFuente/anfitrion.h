#ifndef ANFITRION_H
#define ANFITRION_H
#define MAX_ALOJXANF 30
#include "alojamiento.h"

class Anfitrion {
private:
    string documento;
    unsigned int antiguedad;      // en meses
    float puntuacion;    // de 0.0 a 5.0
    Alojamiento* alojamientos[MAX_ALOJXANF];

public:
    Anfitrion();
    Anfitrion(string doc, unsigned int ant, float punt);

    // Getters
    string getDocumento() const;
    unsigned int getAntiguedad() const;
    float getPuntuacion() const;
    Alojamiento* getAlojamiento(int i) const;
    void agregarAlojamiento(Alojamiento* nuevo, unsigned int& iteraciones);

};

#endif
