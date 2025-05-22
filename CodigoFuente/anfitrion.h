#ifndef ANFITRION_H
#define ANFITRION_H


class Anfitrion {
private:
    unsigned int documento;
    unsigned int antiguedad;      // en meses
    float puntuacion;    // de 0.0 a 5.0


public:
    Anfitrion();
    Anfitrion(unsigned int doc, unsigned int ant, float punt);

    // Getters
    unsigned int getDocumento() const;
    unsigned int getAntiguedad() const;
    float getPuntuacion() const;


};

#endif
