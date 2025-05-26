#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H
#define MAX_RSVXALOJ 50
#include <string>
#include "reservacion.h"
using namespace std;

class Alojamiento {
private:
    unsigned int codigo;
    string nombre;
    string tipo;         // "casa" o "apartamento"
    string direccion;
    string municipio;
    string departamento;
    double precioNoche;
    bool amenidades[6];    // ascensor, piscina, aire, caja, parqueadero, patio

    Reservacion* reservaciones[MAX_RSVXALOJ];

public:
    Alojamiento();
    Alojamiento(unsigned int cod, const string nom, const string tipo, const string dir,
                const string muni, const string depto, double precio, const bool amen[]);

    // Getters
    int getCodigo() const;
    const string getNombre() const;
    const string getTipo() const;
    const string getDireccion() const;
    const string getMunicipio() const;
    const string getDepartamento() const;
    double getPrecioNoche() const;
    bool* getAmenidades();
    Reservacion** getReservaciones() const;


};

#endif
