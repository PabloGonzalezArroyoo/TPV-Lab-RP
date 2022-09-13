// LabEjercicio1.cpp : Pablo González Arroyo y Rafael Argandoña Blácido

#include <iostream>
#include <string>
#include <fstream>

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

struct Alquiler {
    Coche* car;
    string date;
    int days;
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
            cout << lc.elems[i].code << " " << lc.elems[i].price << " " << lc.elems[i].model << endl;
            i++;
        }

        in.close();
        return true;
    }
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

        int i = 0;
        while (i < n) {
            int code;
            in >> code;
            la.elems[i].car = buscarCoche(lc, code);

            in >> la.elems[i].car;
            in.get();
            getline(in, lc.elems[i].model);
            cout << lc.elems[i].code << " " << lc.elems[i].price << " " << lc.elems[i].model << endl;
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
        else i++;
    }

    return car;
}

int main()
{
    // Inicialización de la lista de coches
    ListaCoches lc;
    bool readLc = cargarCoches(lc);
    if (readLc) cout << "\nLEIDO COCHES.TXT\n";
    else cout << "\nNO LEIDO COCHES.TXT\n";

    // Inicialización de la lista de alquileres
    ListaAlquileres la;
    bool readLa = leerAlquileres(la);
    if (readLa) cout << "\nLEIDO RENT.TXT\n";
    else cout << "\nNO LEIDO RENT.TXT\n";
}
