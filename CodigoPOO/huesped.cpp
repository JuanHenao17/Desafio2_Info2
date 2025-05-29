#include "huesped.h"
#include <iostream>

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

Reservacion* Huesped::getReservacion(int i) const {
    if (i >= 0 && i < MAX_RSVXHPD && reservaciones[i] != nullptr){
        return reservaciones[i];
    }

    return nullptr;
}

void Huesped::agregarReservacion(Reservacion* r, unsigned int& iteraciones) {
    for (int i = 0; i < MAX_RSVXHPD; i++) {
        iteraciones++;
        if (reservaciones[i] == nullptr) {
            reservaciones[i] = r;
            return;
        }
    }
    cout << "Huesped con documento " << documento << " ya tiene el maximo de reservas" << endl;
}

void Huesped::eliminarReservacion(Reservacion* r, unsigned int& iteraciones) {
    for (int i = 0; i < MAX_RSVXHPD; i++) {
        iteraciones++;
        if (reservaciones[i] == r) {
            reservaciones[i] = nullptr;
            break;
        }
    }
}

bool Huesped::eliminarReservacionPorCodigo(unsigned int cod, unsigned int& iteraciones) {
    for (int i = 0; i < MAX_RSVXHPD; i++) {
        iteraciones++;
        if (reservaciones[i] != nullptr && reservaciones[i]->getCodigo() == cod) {
            reservaciones[i] = nullptr;
            return true;
        }
    }
    return false;
}
