#ifndef HUESPED_H
#define HUESPED_H
#define MAX_RSVXHPD 50
#include "reservacion.h"

class Huesped {
private:
    string documento;
    unsigned int antiguedad;       // en meses
    float puntuacion;     // de 0.0 a 5.0
    Reservacion* reservaciones[MAX_RSVXHPD];

public:
    Huesped();
    Huesped(string doc, unsigned int ant, float punt);

    // Getters
    string getDocumento() const;
    unsigned int getAntiguedad() const;
    float getPuntuacion() const;
    void agregarReservacion(Reservacion* r, unsigned int& iteraciones);


};

#endif
