#ifndef HUESPED_H
#define HUESPED_H


class Huesped {
private:
    unsigned int documento;
    unsigned int antiguedad;       // en meses
    float puntuacion;     // de 0.0 a 5.0


public:
    Huesped();
    Huesped(unsigned int doc, unsigned int ant, float punt);

    // Getters
    unsigned int getDocumento() const;
    unsigned int getAntiguedad() const;
    float getPuntuacion() const;


};

#endif
