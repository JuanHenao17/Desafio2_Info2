#include <iostream>
#include <fstream>
#include "sistemaudeastay.h"
unsigned int SistemaUdeAStay::totalReservas = 0;

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
        cout << endl << "--- UdeAStay - Menu Principal ---" << endl;
        cout << "1. Iniciar sesion" << endl;
        cout << "2. Salir" <<endl ;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            iniciarSesion();
            break;
        case 2:
            break;
        default:
            cout << "Opcion invalida." << endl;
        }
    } while (opcion != 2);
}

void SistemaUdeAStay::iniciarSesion() {
    unsigned int iteraciones = 0;
    int opcion;
    cout << endl << "== Iniciar sesion ==" << endl;
    cout << "1. Ingresar como huesped" << endl;
    cout << "2. Ingresar como anfitrion" << endl;
    cout << "Ingrese una opcion: ";
    cin >> opcion;

    cin.ignore();
    string doc;

    cout << "Ingrese su numero de documento: ";
    getline(cin, doc);

    if (opcion == 1) {

        for (int i = 0; i < MAX_HUESPEDES && huespedes[i] != nullptr; i++) {
            iteraciones++;
            if (huespedes[i]->getDocumento() == doc) {
                cout << "Recursos utilizados en el inicio de sesion: " << endl;
                cout << "Iteraciones realizadas: " << iteraciones << endl;
                cout << "Acceso concedido." << endl;
                menuHuesped(huespedes[i]);
                return;
            }
        }
        cout << "Recursos utilizados en el inicio de sesion: " << endl;
        cout << "Iteraciones realizadas: " << iteraciones << endl;
        cout << endl << "Documento no registrado como huesped." << endl;

    } else if (opcion == 2) {

        for (int i = 0; i < MAX_ANFITRIONES && anfitriones[i] != nullptr; i++) {
            iteraciones++;
            if (anfitriones[i]->getDocumento() == doc) {
                cout << "Recursos utilizados en el inicio de sesion: " << endl;
                cout << "Iteraciones realizadas: " << iteraciones << endl;
                cout << endl << "Acceso concedido." << endl;
                menuAnfitrion(anfitriones[i]);
                return;
            }
        }
        cout << "Recursos utilizados en el inicio de sesion: " << endl;
        cout << "Iteraciones realizadas: " << iteraciones << endl;
        cout << endl << "Documento no registrado como anfitrion." << endl;
    } else {
        cout << "Opcion invalida." << endl;
    }
}

void SistemaUdeAStay::menuHuesped(Huesped* h) {
    int opcion;
    do {
        cout << endl << "=== Menu Huesped: " << h->getDocumento() << " ===" << endl;
        cout << "1. Reservar alojamiento" << endl;
        cout << "2. Anular una reservacion" << endl;
        cout << "3. Cerrar sesion" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            reservarAlojamiento(h);
            break;
        case 2:
            anularReservacion(h);
            break;
        case 3:
            cout << "Sesion cerrada." << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
        }
    } while (opcion != 3);
}

void SistemaUdeAStay::reservarAlojamiento(Huesped* h) {

    Fecha inicio, fin;
    string municipio;
    unsigned int noches;
    unsigned int iteraciones = 0;
    unsigned int memoria = 0;
    float puntuacionMin;
    double precioMax;

    if(solicitarDatosReserva(inicio, fin, municipio, noches, precioMax, puntuacionMin) == -1){
        return;
    }

    int disponibles[MAX_ALOJAMIENTOS];
    int totalDisponibles = 0;

    for (int i = 0; i < MAX_ALOJAMIENTOS && alojamientos[i] != nullptr; i++) {

        Alojamiento* a = alojamientos[i];

        //Filtro por municipio
        if (a->getMunicipio() != municipio){
            continue;
        }

        //Filtro por precio
        if (precioMax != -1 && a->getPrecioNoche() > precioMax){
            continue;
        }

        //Filtro por puntuación del anfitrión
        Anfitrion* duenio = nullptr;
        for (int j = 0; j < MAX_ANFITRIONES && anfitriones[j] != nullptr; j++) {
            for (int k = 0; k < MAX_ALOJXANF; k++) {
                iteraciones++;
                if (anfitriones[j]->getAlojamiento(k) == a) {
                    duenio = anfitriones[j];
                    break;
                }
            }
            if (duenio != nullptr) {
                break;}
        }

        if (puntuacionMin != -1 && (duenio == nullptr || duenio->getPuntuacion() < puntuacionMin)) {
            continue;
        }

        // Verificar disponibilidad del alojamiento
        bool ocupado = false;
        for (int r = 0; r < MAX_RSVXALOJ; r++) {
            iteraciones++;
            Reservacion* resv = a->getReservacion(r);
            if (resv != nullptr) {
                if (!(fin < resv->getFechaInicio() || inicio > resv->getFechaFin())) {
                    ocupado = true;
                    break;
                }
            }
        }

        if (ocupado) {
            continue; }

        //Verificar que el huésped no tenga otra reserva en esas fechas
        bool conflictoHuesped = false;
        for (int r = 0; r < MAX_RSVXHPD; r++) {
            iteraciones++;
            Reservacion* resv = h->getReservacion(r);
            if (resv != nullptr) {
                if (!(fin < resv->getFechaInicio() || inicio > resv->getFechaFin())) {
                    conflictoHuesped = true;
                    break;
                }
            }
        }

        if (conflictoHuesped) {
            continue; }

        //Agregar indice de candidato e imprimirlo
        disponibles[totalDisponibles] = i;
        totalDisponibles++;

        cout << totalDisponibles << ". Codigo: " << a->getCodigo()
             << " | Nombre: " << a->getNombre()
             << " | Tipo: " << a->getTipo()
             << " | Precio/noche: $" << a->getPrecioNoche();

        if (duenio != nullptr)
            cout << " | Puntuacion del anfitrion: " << duenio->getPuntuacion();

        cout << endl;

    }

    int seleccion;
    cout << endl << "Ingrese el numero del alojamiento que desea reservar (1 a " << totalDisponibles << "): ";
    cin >> seleccion;

    if (seleccion < 1 || seleccion > totalDisponibles) {
        cout << "Seleccion invalida." << endl;
        return;
    }

    int idx = disponibles[seleccion - 1];
    Alojamiento* alojamientoSeleccionado = alojamientos[idx];
    Fecha fechaPago = inicio;

    totalReservas++;
    unsigned int nuevoCodigo = totalReservas;
    double montoTotal = alojamientoSeleccionado->getPrecioNoche() * noches;
    string metodoP;

    if(nuevoCodigo % 2 == 0){
        metodoP = "PSE";
    }
    else{
        metodoP = "Tcredito";
    }

    cin.ignore();
    string anotacion;
    cout << "Ingrese una anotacion para la reserva (max. 1000 caracteres): ";
    getline(cin, anotacion);

    if (anotacion.length() > 1000) {
        anotacion = anotacion.substr(0, 1000);
    }

    Reservacion* nuevaReserva = new Reservacion(nuevoCodigo, inicio, noches,
                                                alojamientoSeleccionado->getCodigo(),
                                                h->getDocumento(), metodoP,
                                                montoTotal, fechaPago, anotacion);

    memoria += sizeof(Reservacion);

    for (int i = 0; i < MAX_RESERVAS; i++) {
        iteraciones++;
        if(reservaciones[i] == nullptr){
            reservaciones[i] = nuevaReserva;
        }
    }

    h->agregarReservacion(nuevaReserva, iteraciones);
    alojamientoSeleccionado->agregarReservacion(nuevaReserva, iteraciones);


    cout << endl << "Reserva confirmada" << endl;
    cout << "Codigo: R" << nuevoCodigo << endl;
    cout << "Huesped: " << h->getDocumento() << endl;
    cout << "Alojamiento: " << alojamientoSeleccionado->getCodigo() << " - " << alojamientoSeleccionado->getNombre() << endl;

    cout << "Fecha de inicio: ";
    inicio.mostrarLarga();

    cout << "Fecha de finalizacion: ";
    nuevaReserva->getFechaFin().mostrarLarga();

    cout << "Total: $" << montoTotal << endl;

    cout << "Recursos utilizados en la reservacion: " << endl;
    cout << "Iteraciones realizadas: " << iteraciones << endl;
    cout << "Memoria estimada: " << memoria << " bytes" << endl;
}

int SistemaUdeAStay::solicitarDatosReserva(Fecha& inicio, Fecha& fin,
                                            string& municipio, unsigned int& noches,
                                                                                      double& precioMax, float& puntuacionMin) {
    int d, m, a;
    char usarFiltros;

    cout << endl << "== Reservar alojamiento ==" << endl;
    cout << "Ingrese la fecha de inicio (dia mes anio): ";
    cin >> d >> m >> a;

    if (!Fecha::fechaValida(d, m, a)) {
        cout << "Fecha invalida. Reserva fallida" << endl ;
        return -1;
    }
    inicio = Fecha(d, m, a);

    cin.ignore();
    cout << "Ingrese el municipio: ";
    getline(cin, municipio);

    cout << "Ingrese la cantidad de noches: ";
    cin >> noches;

    cout << "Desea aplicar filtros? (s/n): ";
    cin >> usarFiltros;

    if (usarFiltros == 's' || usarFiltros == 'S') {
        cout << "Ingrese precio maximo por noche (-1 para ignorar): ";
        cin >> precioMax;
        cout << "Ingrese puntuacion minima del anfitrion (-1 para ignorar): ";
        cin >> puntuacionMin;
    } else {
        precioMax = -1;
        puntuacionMin = -1;
    }

    fin = inicio.sumarDias(noches - 1);
    return 0;
}

void SistemaUdeAStay::anularReservacion(Huesped* h) {
    unsigned int iteraciones = 0;
    unsigned int memoria = 0;
    cout << "\n--- Anular Reservacion ---\n";

    int count = 0;

    for (int i = 0; i < MAX_RSVXHPD; ++i) {
        iteraciones++;
        Reservacion* r = h->getReservacion(i);
        if (r == nullptr) continue;

        cout << "Código: R" << r->getCodigo()
             << " - Alojamiento: " << r->getCodigoAlojamiento()
             << " - Fecha inicio: ";
        r->getFechaInicio().mostrarCorta();
        cout << endl;

        count++;
    }

    if (count == 0) {
        cout << "No tienes reservaciones activas.\n";
        return;
    }

    cout << "Ingrese el codigo de la reserva a anular (solo numero, sin 'R'): ";
    unsigned int codigo;
    cin >> codigo;

    // Eliminar del huesped
    bool eliminada = h->eliminarReservacionPorCodigo(codigo, iteraciones);

    // Eliminar del alojamiento
    for (int i = 0; i < MAX_ALOJAMIENTOS && alojamientos[i] != nullptr; i++) {
        alojamientos[i]->eliminarReservacionPorCodigo(codigo, iteraciones);
    }

    // Eliminar del arreglo global
    for (int i = 0; i < MAX_RESERVAS; ++i) {
        iteraciones++;
        if (reservaciones[i] != nullptr && reservaciones[i]->getCodigo() == codigo) {
            memoria += sizeof(Reservacion);
            delete reservaciones[i];
            reservaciones[i] = nullptr;
            break;
        }
    }

    if (eliminada) {
        cout << "Recursos utilizados en la anulacion: " << endl;
        cout << "Iteraciones realizadas: " << iteraciones << endl;
        cout << "Memoria liberada estimada: " << memoria << " bytes" << endl;
        cout << endl << "Reservacion anulada exitosamente.\n";

    } else {
        cout << "Recursos utilizados en la anulacion: " << endl;
        cout << "Iteraciones realizadas: " << iteraciones << endl;
        cout << "Memoria liberada estimada: " << memoria << " bytes" << endl;
        cout << endl << "No se encontro una reservacion con ese codigo.\n";
    }
}

void SistemaUdeAStay::menuAnfitrion(Anfitrion* a) {
    int opcion;
    do {
        cout << endl << "=== Menu Anfitrion: " << a->getDocumento() << " ===" << endl;
        cout << "1. Anular una reservacion" << endl;
        cout << "2. Consultar reservaciones de mis alojamientos" << endl;
        cout << "3. Actualizar historico de reservas" << endl;
        cout << "4. Cerrar sesion" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            anularReservacion(a);
            break;
        case 2:
            consultarReservasAnfitrion(a);
            break;
        case 3:
            actualizarHistorico();
            break;
        case 4:
            cout << "Sesion cerrada." << endl;
            break;
        default:
            cout << "Opción inválida." << endl;
        }
    } while (opcion != 4);
}

void SistemaUdeAStay::anularReservacion(Anfitrion* a) {
    unsigned int memoria = 0;
    unsigned int iteraciones = 0;
    cout << "\n--- Anular Reservacion ---\n";

    // Mostrar alojamientos disponibles
    int indicesValidos[MAX_ALOJXANF];
    int countAlojamientos = 0;

    for (int i = 0; i < MAX_ALOJXANF; ++i) {
        iteraciones++;
        Alojamiento* alo = a->getAlojamiento(i);
        if (alo == nullptr) break;

        cout << countAlojamientos + 1 << ". " << alo->getCodigo()
             << " - " << alo->getDireccion() << endl;
        indicesValidos[countAlojamientos] = i;
        countAlojamientos++;
    }

    if (countAlojamientos == 0) {
        cout << "El anfitrion no tiene alojamientos registrados.\n";
        return;
    }

    cout << "Seleccione el alojamiento (numero): ";
    int opcion;
    cin >> opcion;

    if (opcion < 1 || opcion > countAlojamientos) {
        cout << "Opcion invalida.\n";
        return;
    }

    Alojamiento* seleccionado = a->getAlojamiento(indicesValidos[opcion - 1]);

    // Mostrar reservaciones de ese alojamiento
    int countReservas = 0;

    for (int i = 0; i < MAX_RSVXALOJ; ++i) {
        iteraciones++;
        Reservacion* r = seleccionado->getReservacion(i);
        if (r == nullptr) continue;

        cout << "Codigo: " << r->getCodigo()
             << " - Huesped: " << r->getDocumentoHuesped() << endl;

        countReservas++;
    }

    if (countReservas == 0) {
        cout << "Este alojamiento no tiene reservas.\n";
        return;
    }

    cout << "Ingrese el codigo de la reserva a anular: ";
    unsigned int codigo;
    cin >> codigo;

    // Eliminar de alojamiento
    bool eliminada = seleccionado->eliminarReservacionPorCodigo(codigo, iteraciones);

    // Eliminar de huésped
    for (int i = 0; i < MAX_HUESPEDES && huespedes[i] != nullptr; i++) {
        huespedes[i]->eliminarReservacionPorCodigo(codigo, iteraciones);
    }

    // Eliminar de arreglo general
    for (int i = 0; i < MAX_RESERVAS; ++i) {
        iteraciones++;
        if (reservaciones[i] != nullptr && reservaciones[i]->getCodigo() == codigo) {
            memoria += sizeof(Reservacion);
            delete reservaciones[i];
            reservaciones[i] = nullptr;
            break;
        }
    }

    if (eliminada) {

        cout << "Recursos utilizados en la anulacion: " << endl;
        cout << "Iteraciones realizadas: " << iteraciones << endl;
        cout << "Memoria liberada estimada: " << memoria << " bytes" << endl;
        cout << endl << "Reservacion anulada exitosamente.\n";

    } else {
        cout << "Recursos utilizados en la anulacion: " << endl;
        cout << "Iteraciones realizadas: " << iteraciones << endl;
        cout << "Memoria liberada estimada: " << memoria << " bytes" << endl;
        cout << endl << "No se encontro una reservacion con ese codigo en el alojamiento seleccionado.\n";
    }
}

void SistemaUdeAStay::consultarReservasAnfitrion(Anfitrion* a) {

    unsigned int iteraciones = 0;

    cout << "\n--- Reservas de los alojamientos del anfitrion: " << a->getDocumento() << " ---\n";

    cout << endl << "Ingrese fecha de inicio del rango (formato DD-MM-AAAA): ";
    string inicioStr;
    getline(cin >> ws, inicioStr);
    Fecha fechaInicioFiltro = Fecha::desdeCadena(inicioStr);

    if (!Fecha::fechaValida(fechaInicioFiltro.getDia(), fechaInicioFiltro.getMes(), fechaInicioFiltro.getAnio())) {
        cout << "Fecha invalida. Consulta fallida" << endl ;
        return;
    }

    cout << endl << "Ingrese fecha de fin del rango (formato DD-MM-AAAA): ";
    string finStr;
    getline(cin, finStr);
    Fecha fechaFinFiltro = Fecha::desdeCadena(finStr);

    if (!Fecha::fechaValida(fechaFinFiltro.getDia(), fechaFinFiltro.getMes(), fechaFinFiltro.getAnio())) {
        cout << "Fecha invalida. Consulta fallida" << endl ;
        return;
    }

    for (int i = 0; i < MAX_ALOJXANF; i++) {
        Alojamiento* aloja = a->getAlojamiento(i);

        if(aloja == nullptr){
            return;
        }

        cout << endl << "Alojamiento #" << aloja->getCodigo() << " - " << aloja->getDireccion() << endl;

        for (int j = 0; j < MAX_RSVXALOJ; j++) {
            iteraciones++;
            Reservacion* r = aloja->getReservacion(j);

            if(r==nullptr){
                break;
            }

            Fecha fi = r->getFechaInicio();
            Fecha ff = r->getFechaFin();

            if (ff < fechaInicioFiltro || fi > fechaFinFiltro) {
                continue;
            }

            cout << " Reserva #" << r->getCodigo() << " - Huesped: " << r->getDocumentoHuesped() << endl;
            cout << " Fecha Inicio: ";
            fi.mostrarCorta();
            cout << " Fecha fin: ";
            ff.mostrarCorta();
        }
    }
    cout << "Recursos utilizados en la consulta: " << endl;
    cout << "Iteraciones realizadas: " << iteraciones << endl;
}


void SistemaUdeAStay::actualizarHistorico(){

    unsigned int iteraciones = 0;
    unsigned int memoria = 0;
    int d, m, a;
    cout << "Ingrese la fecha de corte (dia mes anio): ";
    cin >> d >> m >> a;

    if (!Fecha::fechaValida(d, m, a)) {
        cout << "Fecha invalida." << endl;
        return;
    }

    Fecha fechaCorte(d, m, a);

    ofstream historico("reservas_historicas.txt", ios::app);
    if (!historico.is_open()) {
        cout << "No se pudo abrir reservas_historicas.txt para escritura." << endl;
        return;
    }

    ifstream verificador("reservas_historicas.txt");
    if (verificador.is_open()) {
        verificador.seekg(-1, ios::end);
        char ultimo;
        verificador.get(ultimo);
        if (ultimo != '\n') historico << endl;
        verificador.close();
    }

    for (int i = 0; i < MAX_RESERVAS; i++) {
        iteraciones++;
        Reservacion* r = reservaciones[i];
        if (r != nullptr && r->getFechaFin() < fechaCorte) {
            memoria+= sizeof(Reservacion);
            // Escribir en archivo historico
            historico << "R" << r->getCodigo() << ";"
                      << r->getCodigoAlojamiento() << ";"
                      << r->getDocumentoHuesped() << ";"
                      << r->getFechaInicio().FechaAstr() << ";"
                      << r->getNoches() << ";"
                      << r->getMetodoPago() << ";"
                      << r->getFechaPago().FechaAstr() << ";"
                      << r->getMonto() << ";"
                      << r->getNota() << endl;

            // Quitar de huesped
            for (int h = 0; h < MAX_HUESPEDES && huespedes[h] != nullptr; h++) {
                iteraciones++;
                if (huespedes[h]->getDocumento() == r->getDocumentoHuesped()) {
                    huespedes[h]->eliminarReservacion(r, iteraciones);
                    break;
                }
            }

            // Quitar de alojamiento
            for (int a = 0; a < MAX_ALOJAMIENTOS && alojamientos[a] != nullptr; a++) {
                iteraciones++;
                if (alojamientos[a]->getCodigo() == r->getCodigoAlojamiento()) {
                    alojamientos[a]->eliminarReservacion(r, iteraciones);
                    break;
                }
            }

            // Eliminar del arreglo global
            delete r;
            reservaciones[i] = nullptr;

        }
    }

    ofstream reservasOut("reservas.txt");
    if (!reservasOut.is_open()) {
        cout << "No se pudo abrir reservas.txt para actualizaciOn" << endl;
        return;
    }

    for (int i = 0; i < MAX_RESERVAS; i++) {
        iteraciones++;
        if(reservaciones[i] != nullptr){

            Reservacion* r = reservaciones[i];
            reservasOut << "R" << r->getCodigo() << ";"
                        << r->getCodigoAlojamiento() << ";"
                        << r->getDocumentoHuesped() << ";"
                        << r->getFechaInicio().FechaAstr() << ";"
                        << r->getNoches() << ";"
                        << r->getMetodoPago() << ";"
                        << r->getFechaPago().FechaAstr() << ";"
                        << r->getMonto() << ";"
                        << r->getNota() << endl;

        }
    }

    reservasOut.close();

    cout << "Recursos utilizados en la actualizacion: " << endl;
    cout << "Iteraciones realizadas: " << iteraciones << endl;
    cout << "Memoria liberada estimada: " << memoria << " bytes" << endl;
    cout << endl << "Archivos actualizados correctamente" << endl;

}

void SistemaUdeAStay::cargarDatos() {
    unsigned int iteraciones = 0;
    unsigned int memoria = 0;

    cargarAnfitriones(iteraciones, memoria);
    cargarHuespedes(iteraciones, memoria);
    cargarAlojamientos(iteraciones, memoria);
    cargarReservas(iteraciones, memoria);
    contarReservasHistoricas(iteraciones);

    cout << "Recursos utilizados en la carga de archivos: " << endl;
    cout << "Iteraciones realizadas: " << iteraciones << endl;
    cout << "Memoria estimada: " << memoria << " bytes" << endl;
}

void SistemaUdeAStay::cargarAnfitriones(unsigned int& iteraciones, unsigned int& memoria) {
    ifstream archivo("anfitriones.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo anfitriones.txt" << endl;
        return;
    }

    string linea;
    int index = 0;

    while (getline(archivo, linea) && index < MAX_ANFITRIONES) {
        iteraciones++;
        if (linea.empty()) continue;

        size_t pos1 = linea.find(';');
        size_t pos2 = linea.find(';', pos1 + 1);

        string doc = linea.substr(0, pos1);
        string campo2 = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        string campo3 = linea.substr(pos2 + 1);

        unsigned int antiguedad = stoi(campo2);
        float puntuacion = stof(campo3);

        anfitriones[index] = new Anfitrion(doc, antiguedad, puntuacion);
        memoria += sizeof(Anfitrion);
        index++;
    }

    archivo.close();

}

void SistemaUdeAStay::cargarHuespedes(unsigned int& iteraciones, unsigned int& memoria) {
    ifstream archivo("huespedes.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo huespedes.txt" << endl;
        return;
    }

    string linea;
    int index = 0;

    while (getline(archivo, linea) && index < MAX_HUESPEDES) {
        iteraciones++;
        if (linea.empty()) continue;

        size_t pos1 = linea.find(';');
        size_t pos2 = linea.find(';', pos1 + 1);

        string doc = linea.substr(0, pos1);
        string campo2 = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        string campo3 = linea.substr(pos2 + 1);

        unsigned int antiguedad = stoi(campo2);
        float puntuacion = stof(campo3);

        huespedes[index] = new Huesped(doc, antiguedad, puntuacion);
        memoria += sizeof(Huesped);
        index++;
    }

    archivo.close();
}

void SistemaUdeAStay::cargarAlojamientos(unsigned int& iteraciones, unsigned int& memoria) {
    ifstream archivo("alojamientos.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo alojamientos.txt" << endl;
        return;
    }

    string linea;
    int index = 0;

    while (getline(archivo, linea) && index < MAX_ALOJAMIENTOS) {
        iteraciones++;
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
        iteraciones += 6;

        Alojamiento* nuevo = new Alojamiento(codigo, "Aloj" + to_string(codigo), tipo, dir, muni, depto, precio, amen);
        alojamientos[index] = nuevo;
        memoria += sizeof(Alojamiento);
        index++;

        bool encontrado = false;
        for (int i = 0; i < MAX_ANFITRIONES && anfitriones[i] != nullptr; i++) {
            iteraciones++;
            if (anfitriones[i]->getDocumento() == docAnfitrion) {
                anfitriones[i]->agregarAlojamiento(nuevo, iteraciones);
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            cout << " No se encontro anfitrion con documento: " << docAnfitrion << endl;
        }
    }

    archivo.close();
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

void SistemaUdeAStay::cargarReservas(unsigned int& iteraciones, unsigned int& memoria) {
    ifstream archivo("reservas.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo reservas.txt" << endl;
        return;
    }

    string linea;
    int index = 0;

    while (getline(archivo, linea) && index < MAX_RESERVAS) {
        iteraciones++;
        if (linea.empty()) continue;

        size_t p1 = linea.find(';');
        size_t p2 = linea.find(';', p1 + 1);
        size_t p3 = linea.find(';', p2 + 1);
        size_t p4 = linea.find(';', p3 + 1);
        size_t p5 = linea.find(';', p4 + 1);
        size_t p6 = linea.find(';', p5 + 1);
        size_t p7 = linea.find(';', p6 + 1);
        size_t p8 = linea.find(';', p7 + 1);

        string codReserva = linea.substr(0, p1);
        string scodAloj = linea.substr(p1 + 1, p2 - p1 - 1);
        string docHuesp = linea.substr(p2 + 1, p3 - p2 - 1);
        string fechaInicio = linea.substr(p3 + 1, p4 - p3 - 1);
        string snoches = linea.substr(p4 + 1, p5 - p4 - 1);
        string metodo = linea.substr(p5 + 1, p6 - p5 - 1);
        string fechaPago = linea.substr(p6 + 1, p7 - p6 - 1);
        string smonto = linea.substr(p7 + 1, p8 - p7 - 1);
        string nota = linea.substr(p8 + 1);

        Fecha ini = Fecha::desdeCadena(fechaInicio);
        Fecha fin = Fecha::desdeCadena(fechaPago);

        unsigned int codigo = stoi(codReserva.substr(1));
        unsigned int codigoAlojamiento = stoi(scodAloj);
        unsigned int noches = stoi(snoches);
        float monto = stof(smonto);

        Reservacion* r = new Reservacion(codigo, ini, noches, codigoAlojamiento,
                                         docHuesp, metodo, monto, fin, nota);

        reservaciones[index] = r;
        memoria += sizeof(Reservacion);
        totalReservas++;
        index++;

        for (int i = 0; i < MAX_HUESPEDES && huespedes[i] != nullptr; i++) {
            iteraciones++;
            if (huespedes[i]->getDocumento() == docHuesp) {
                huespedes[i]->agregarReservacion(r, iteraciones);
                break;
            }
        }

        for (int i = 0; i < MAX_ALOJAMIENTOS && alojamientos[i] != nullptr; i++) {
            iteraciones++;
            if (alojamientos[i]->getCodigo() == codigoAlojamiento) {
                alojamientos[i]->agregarReservacion(r, iteraciones);
                break;
            }
        }
    }

    archivo.close();
}

void SistemaUdeAStay::contarReservasHistoricas(unsigned int& iteraciones) {
    ifstream archivo("reservas_historicas.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir reservas_historicas.txt" << endl;
        return;
    }

    string linea;

    while (getline(archivo, linea)) {
        iteraciones++;
        if (!linea.empty()) {
            totalReservas++;
        }
    }

    archivo.close();
}
