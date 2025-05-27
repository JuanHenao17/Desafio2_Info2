#ifndef FECHA_H
#define FECHA_H
#include <string>
using namespace std;

class Fecha {

private:
    int dia;
    int mes;
    int anio;

public:
    Fecha();
    Fecha(int d, int m, int a);
    Fecha(const Fecha& otra);

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    Fecha& operator=(const Fecha& otra);
    bool operator==(const Fecha& otra) const;
    bool operator<(const Fecha& otra) const;
    bool operator>(const Fecha& otra) const;
    bool operator<=(const Fecha& otra) const;
    bool operator>=(const Fecha& otra) const;

    // Utilidades

    static bool fechaValida(int d, int m, int a);
    static int diasEnMes(int mes, int anio);
    static string nombreMes(int m);
    static string nombreDiaSemana(int d, int m, int a);
    Fecha sumarDias(int n) const;
    void mostrarLarga() const;
    void mostrarCorta() const;
    static Fecha desdeCadena(const string& s);
};

#endif // FECHA_H
