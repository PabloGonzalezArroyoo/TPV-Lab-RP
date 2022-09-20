// LabEjercicio1.cpp : Pablo González Arroyo y Rafael Argandoña Blácido

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <tuple>

using namespace std;

struct Coche {
    int code;
    int price;
    string model;
};

struct ListaCoches {
    Coche* elems = new Coche[cap]; // Array dinámico
    int cap;
    int cont;
};

struct Alquiler {
    Coche* car;
    string date;
    int days;
};

struct ListaAlquileres {
    Alquiler* elems = new Alquiler[cap];
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
            la.elems[i].car = buscarCoche(lc, code);

            in >> la.elems[i].date;
            in.get();
            getline(in, lc.elems[i].model);
            cout << lc.elems[i].code << " " << lc.elems[i].price << " " << lc.elems[i].model << endl;
            i++;
        }

        in.close();
        return true;
    }
}

tuple<int, int, int> Split(string date) {
    int anio, mes, dia;

    int i = 0; int contador = 0;
    string c = "";
    for (int i = 0; i < date.size(); i++) {
        c += date[i];
        
        if (c == "/" && contador == 0) {
            dia = stoi(c);
            c = "";
            contador++;
        }
        else if (c == "/" && contador == 1) {
            mes = stoi(c);
            c = "";
            contador++;
        }
    }

    anio = stoi(c);

    return make_tuple(anio, mes, dia);
}

// Ver si fecha1 es menor que fecha2
bool compararFechas(Alquiler al1, Alquiler al2) {
    tuple<int, int, int> fecha1 = Split(al1.date);
    tuple<int, int, int> fecha2 = Split(al2.date);
    
    int anio1 = get<0>(fecha1); int mes1 = get<1>(fecha1); int dia1 = get<2>(fecha1);
    int anio2 = get<0>(fecha2); int mes2 = get<1>(fecha2); int dia2 = get<2>(fecha2);
    
    if (anio1 < anio2) return true;
    else if (anio1 == anio2) {

        if (mes1 < mes2) return true;
        else if (mes1 == mes2) {

            if (dia1 < dia2) return true;
            else return false;
        }
        else return false;
    }
    else return false;
}

void ordenaAlquileres(ListaAlquileres& la)
{
    sort(la.elems[0].date, la.elems[la.cont-1].date, compararFechas(la.elems[0], la.elems[la.cont - 1]));
}

void mostrarAlquileres(ListaAlquileres la)
{
    for (int i = 0; i < la.cont; i++)
    {
        cout << la.elems[i].date << " " << la.elems[i].car->model << " " << la.elems[i].days 
            << " dia(s) por " << la.elems[i].car->price * la.elems[i].days << " euros " << endl;
    }
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
    bool readLa = leerAlquileres(la, lc);
    if (readLa) cout << "\nLEIDO RENT.TXT\n";
    else cout << "\nNO LEIDO RENT.TXT\n";
}
