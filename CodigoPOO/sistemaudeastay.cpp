#include <iostream>
#include <fstream>
#include "sistemaudeastay.h"

SistemaUdeAStay::SistemaUdeAStay() {
    for (int i = 0; i < MAX_HUESPEDES; i++) {
        huespedes[i] = nullptr; }
    for (int i = 0; i < MAX_ANFITRIONES; i++) {
        anfitriones[i] = nullptr; }
    for (int i = 0; i < MAX_ALOJAMIENTOS; i++) {
        alojamientos[i] = nullptr; }
    for (int i = 0; i < MAX_RESERVAS; i++) {
        reservaciones[i] = nullptr; }
}

SistemaUdeAStay::~SistemaUdeAStay() {
    for (int i = 0; i < MAX_HUESPEDES; i++) {
        delete huespedes[i];}
    for (int i = 0; i < MAX_ANFITRIONES; i++) {
        delete anfitriones[i]; }
    for (int i = 0; i < MAX_ALOJAMIENTOS; i++) {
        delete alojamientos[i]; }
    for (int i = 0; i < MAX_RESERVAS; i++) {
        delete reservaciones[i]; }
}

void SistemaUdeAStay::mostrarMenu() {
    int opcion;

    do {
        cout << "\n--- UdeAStay - Menu Principal ---\n";
        cout << "1. Iniciar sesion\n";
        cout << "2. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Funcionalidad de login pendiente de implementar.\n";
            break;
        case 2:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 2);
}

void SistemaUdeAStay::cargarDatos() {
    cargarAnfitriones();
    cargarHuespedes();
    cargarAlojamientos();
    // Luego agregarás aquí: cargarHuespedes(), cargarAlojamientos(), etc.
}

void SistemaUdeAStay::cargarAnfitriones() {
    ifstream archivo("anfitriones.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo anfitriones.txt" << endl;
        return;
    }

    string linea;
    int index = 0;

    while (getline(archivo, linea) && index < MAX_ANFITRIONES) {
        if (linea.empty()) continue;

        size_t pos1 = linea.find(';');
        size_t pos2 = linea.find(';', pos1 + 1);

        string doc = linea.substr(0, pos1);                          // documento
        string campo2 = linea.substr(pos1 + 1, pos2 - pos1 - 1);        // antigüedad
        string campo3 = linea.substr(pos2 + 1);                         // puntuación

        unsigned int antiguedad = stoi(campo2);
        float puntuacion = stof(campo3);

        anfitriones[index] = new Anfitrion(doc, antiguedad, puntuacion);
        index++;
    }

    archivo.close();

    cout << "Se cargaron " << index << " anfitriones correctamente." << endl;
}

void SistemaUdeAStay::cargarHuespedes() {
    ifstream archivo("huespedes.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo huespedes.txt" << endl;
        return;
    }

    string linea;
    int index = 0;

    while (getline(archivo, linea) && index < MAX_HUESPEDES) {
        if (linea.empty()) continue;

        size_t pos1 = linea.find(';');
        size_t pos2 = linea.find(';', pos1 + 1);

        string doc = linea.substr(0, pos1);
        string campo2 = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        string campo3 = linea.substr(pos2 + 1);

        unsigned int antiguedad = stoi(campo2);
        float puntuacion = stof(campo3);

        huespedes[index] = new Huesped(doc, antiguedad, puntuacion);
        index++;
    }

    archivo.close();
    cout << "Se cargaron " << index << " huespedes correctamente." << endl;
}

void SistemaUdeAStay::cargarAlojamientos() {
    ifstream archivo("alojamientos.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo alojamientos.txt" << endl;
        return;
    }

    string linea;
    int index = 0;

    while (getline(archivo, linea) && index < MAX_ALOJAMIENTOS) {
        if (linea.empty()) continue;

        size_t p1 = linea.find(';');
        size_t p2 = linea.find(';', p1 + 1);
        size_t p3 = linea.find(';', p2 + 1);
        size_t p4 = linea.find(';', p3 + 1);
        size_t p5 = linea.find(';', p4 + 1);
        size_t p6 = linea.find(';', p5 + 1);
        size_t p7 = linea.find(';', p6 + 1);

        string scod      = linea.substr(0, p1);
        string sdocAnf   = linea.substr(p1 + 1, p2 - p1 - 1);
        string depto     = linea.substr(p2 + 1, p3 - p2 - 1);
        string muni      = linea.substr(p3 + 1, p4 - p3 - 1);
        string tipo      = linea.substr(p4 + 1, p5 - p4 - 1);
        string dir       = linea.substr(p5 + 1, p6 - p5 - 1);
        string sprecio   = linea.substr(p6 + 1, p7 - p6 - 1);
        string samen     = linea.substr(p7 + 1);

        unsigned int codigo = stoi(scod);
        string docAnfitrion = sdocAnf;
        double precio = stod(sprecio);

        bool amen[6];
        interpretarAmenidades(samen, amen);

        Alojamiento* nuevo = new Alojamiento(codigo, "Aloj" + to_string(codigo), tipo, dir, muni, depto, precio, amen);
        alojamientos[index] = nuevo;
        index++;

        bool encontrado = false;
        for (int i = 0; i < MAX_ANFITRIONES && anfitriones[i] != nullptr; i++) {
            if (anfitriones[i]->getDocumento() == docAnfitrion) {
                anfitriones[i]->agregarAlojamiento(nuevo);
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            cout << " No se encontro anfitrion con documento: " << docAnfitrion << endl;
        }
    }

    archivo.close();
    cout << "Se cargaron " << index << " alojamientos correctamente." << endl;
}

void SistemaUdeAStay::interpretarAmenidades(const string& cadena, bool amenidades[6]) {

    for (int i = 0; i < 6; i++) {
        amenidades[i] = false;
    }

    if (cadena.find("ascensor") != string::npos){
        amenidades[0] = true;}
    if (cadena.find("piscina") != string::npos){
        amenidades[1] = true;}
    if (cadena.find("aire") != string::npos){
        amenidades[2] = true;}
    if (cadena.find("caja") != string::npos){
        amenidades[3] = true;}
    if (cadena.find("parqueadero") != string::npos){
        amenidades[4] = true;}
    if (cadena.find("patio") != string::npos){
        amenidades[5] = true;}
}
