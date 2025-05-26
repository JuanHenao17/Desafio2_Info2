#ifndef SISTEMAUDEASTAY_H
#define SISTEMAUDEASTAY_H
#define MAX_HUESPEDES 50
#define MAX_ANFITRIONES 50
#define MAX_ALOJAMIENTOS 100
#define MAX_RESERVAS 200

#include "huesped.h"
#include "anfitrion.h"
#include "alojamiento.h"
#include "reservacion.h"

class SistemaUdeAStay{
private:

    Huesped* huespedes[MAX_HUESPEDES];
    Anfitrion* anfitriones[MAX_ANFITRIONES];
    Alojamiento* alojamientos[MAX_ALOJAMIENTOS];
    Reservacion* reservaciones[MAX_RESERVAS];

public:
    SistemaUdeAStay();
    ~SistemaUdeAStay();
    void mostrarMenu();
    void cargarDatos();
    void cargarAnfitriones(unsigned int& iteraciones, unsigned int& memoria);
    void cargarHuespedes(unsigned int& iteraciones, unsigned int& memoria);
    void cargarAlojamientos(unsigned int& iteraciones, unsigned int& memoria);
    void interpretarAmenidades(const string& cadena, bool amenidades[6]);
    void cargarReservas(unsigned int& iteraciones, unsigned int& memoria);

};

#endif // SISTEMAUDEASTAY_H
