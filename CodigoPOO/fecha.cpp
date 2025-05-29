#include "fecha.h"
#include <iostream>
#include <string>
using namespace std;

Fecha::Fecha() : dia(1), mes(1), anio(2000) {}

Fecha::Fecha(int d, int m, int a) : dia(d), mes(m), anio(a) {}

Fecha::Fecha(const Fecha& otra) : dia(otra.dia), mes(otra.mes), anio(otra.anio) {}

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

Fecha& Fecha::operator=(const Fecha& otra) {
    if (this != &otra) {
        this->dia  = otra.dia;
        this->mes  = otra.mes;
        this->anio = otra.anio;
    }
    return *this;
}


bool Fecha::operator==(const Fecha& otra) const {
    return dia == otra.dia && mes == otra.mes && anio == otra.anio;
}

bool Fecha::operator<(const Fecha& otra) const {
    if (anio != otra.anio) return anio < otra.anio;
    if (mes != otra.mes) return mes < otra.mes;
    return dia < otra.dia;
}

bool Fecha::operator>(const Fecha& otra) const {
    return otra < *this;
}

bool Fecha::operator<=(const Fecha& otra) const {
    return !(*this > otra);
}

bool Fecha::operator>=(const Fecha& otra) const {
    return !(*this < otra);
}

bool Fecha::fechaValida(int d, int m, int a) {
    if (m < 1 || m > 12) return false;
    if (a < 1900 || a > 2100) return false;

    int maxDia = diasEnMes(m, a);
    return d >= 1 && d <= maxDia;
}

int Fecha::diasEnMes(int mes, int anio) {
    switch (mes) {
    case 2: return (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0)) ? 29 : 28;
    case 4: case 6: case 9: case 11: return 30;
    default: return 31;
    }
}

string Fecha::nombreMes(int m) {
    string meses[] = { "", "enero", "febrero", "marzo", "abril", "mayo", "junio",
                      "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre" };
    return meses[m];
}

string Fecha::nombreDiaSemana(int d, int m, int a) {
    if (m < 3) {
        m += 12;
        a--;
    }

    int k = a % 100;
    int j = a / 100;

    int h = (d + 13*(m + 1)/5 + k + k/4 + j/4 + 5*j) % 7;
    string dias[] = { "sabado", "domingo", "lunes", "martes", "miercoles", "jueves", "viernes" };

    return dias[h];
}

Fecha Fecha::sumarDias(int n) const {
    int d = dia, m = mes, a = anio;

    while (n > 0) {
        int diasMes = diasEnMes(m, a);
        int restantes = diasMes - d;

        if (n <= restantes) {
            d += n;
            break;
        } else {
            n -= (restantes + 1);
            d = 1;
            m++;
            if (m > 12) {
                m = 1;
                a++;
            }
        }
    }

    return Fecha(d, m, a);
}

void Fecha::mostrarLarga() const {
    cout << nombreDiaSemana(dia, mes, anio) << ", " << dia
         << " de " << nombreMes(mes) << " del " << anio << endl;
}

void Fecha::mostrarCorta()const{
    cout << dia << "/" << mes << "/" << anio << endl;
}

Fecha Fecha::desdeCadena(const string& s) {
    int d, m, a;
    size_t pos1 = s.find('-');
    size_t pos2 = s.find('-', pos1 + 1);

    d = stoi(s.substr(0, pos1));
    m = stoi(s.substr(pos1 + 1, pos2 - pos1 - 1));
    a = stoi(s.substr(pos2 + 1));

    return Fecha(d, m, a);
}

string Fecha::FechaAstr() const {
    string d = (dia < 10 ? "0" : "") + to_string(dia);
    string m = (mes < 10 ? "0" : "") + to_string(mes);
    string a = to_string(anio);
    return d + "-" + m + "-" + a;
}
