// LabEjercicio1.cpp : Pablo González Arroyo y Rafael Argandoña Blácido

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct Coche {
    int code;
    int price;
    string model;
};

struct ListaCoches {
    Coche* elems; // Array dinámico
    int cap;
    int cont;
};

struct Fecha {
    int dia;
    int mes;
    int anio;
};

struct Alquiler {
    Coche* car;
    Fecha date;
    int days;


    bool operator<(const Alquiler& other) {
        if (date.anio < other.date.anio) return true;
        else if (date.anio == other.date.anio) {

            if (date.mes < other.date.mes) return true;
            else if (date.mes == other.date.mes) {

                if (date.dia < other.date.dia) return true;
                else return false;
            }
            else return false;
        }
        else return false;
    }
};

struct ListaAlquileres {
    Alquiler* elems;
    int cap;
    int cont;
};

bool cargarCoches(ListaCoches& lc) {
    ifstream in;
    in.open("coches.txt");
    if (!in.is_open()) return false;
    else {
        int n;
        in >> n;
        lc.elems = new Coche[n];
        lc.cont = n;
        lc.cap = lc.cont + 10;

        int i = 0;
        while (i < n) {
            in >> lc.elems[i].code;
            in >> lc.elems[i].price;
            in.get();
            getline(in, lc.elems[i].model);
            std::cout << lc.elems[i].code << " " << lc.elems[i].price << " " << lc.elems[i].model << endl;
            i++;
        }

        in.close();
        return true;
    }
}

Coche* buscarCoche(ListaCoches lc, int code) {
    Coche* car = nullptr;

    int i = 0;
    bool found = false;
    while (!found && i < lc.cont) {
        if (lc.elems[i].code == code) {
            car = &lc.elems[i];
            found = true;
        }
        i++;
    }

    return car;
}

Fecha Split(string date) {
    int anio = 0, mes = 0, dia = 0;
    Fecha f;

    int i = 0; int contador = 0;
    string c = "";
    for (int i = 0; i < date.size(); i++) {
        if (date[i] == '/' && contador == 0) {
            dia = stoi(c);
            c = "";
            contador++;
        }
        else if (date[i] == '/' && contador == 1) {
            mes = stoi(c);
            c = "";
            contador++;
        }
        else c += date[i];
    }
    anio = stoi(c);
    f.dia = dia;
    f.mes = mes;
    f.anio = anio;

    return f;
}

bool leerAlquileres(ListaAlquileres& la, ListaCoches lc) {
    ifstream in;
    in.open("rent.txt");
    if (!in.is_open()) return false;
    else {
        int n;
        in >> n;
        la.elems = new Alquiler[n];
        la.cont = n;
        la.cap = la.cont + 10;

        for (int i = 0; i < n; i++) {
            int code;
            in >> code;
            string date;
            in >> date;
            in.get();
            int days;
            in >> days;

            la.elems[i].date = Split(date);
            la.elems[i].car = buscarCoche(lc, code);
            la.elems[i].days = days;
            // cout << i << " - ";
            // cout << (la.elems[i].car)->model << " " << la.elems[i].date.anio << " " << la.elems[i].days << endl;
        }

        in.close();
        return true;
    }
}

void ordenaAlquileres(ListaAlquileres& la)
{
    sort(&(la.elems[0]), &(la.elems[la.cont]));
}

void mostrarAlquileres(ListaAlquileres la)
{
    for (int i = 0; i < la.cont; i++)
    {
        if (la.elems[i].car != nullptr) {
            std::cout << la.elems[i].date.dia << "/" << la.elems[i].date.mes << "/" << la.elems[i].date.anio << " "
                << la.elems[i].car->model << " " << la.elems[i].days << " dia(s) por "
                << la.elems[i].car->price * la.elems[i].days << " euros " << endl;
        }
        else {
            std::cout << la.elems[i].date.dia << "/" << la.elems[i].date.mes << "/" << la.elems[i].date.anio << " " <<
                "ERROR: Modelo inexistente" << endl;
        }
    }
}

int main()
{
    // Inicialización de la lista de coches
    ListaCoches lc;
    bool readLc = cargarCoches(lc);
    if (readLc) std::cout << "\nLEIDO COCHES.TXT\n";
    else std::cout << "\nNO LEIDO COCHES.TXT\n";

    // Inicialización de la lista de alquileres
    ListaAlquileres la;
    bool readLa = leerAlquileres(la, lc);
    if (readLa) std::cout << "\n\nLEIDO RENT.TXT\n";
    else std::cout << "\nNO LEIDO RENT.TXT\n";

    ordenaAlquileres(la);
    mostrarAlquileres(la);
}
