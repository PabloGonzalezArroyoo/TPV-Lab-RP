#include "ListaCoches.h"

#include <fstream>
#include <string>
#include <iostream>

ListaCoches::ListaCoches() : elems(), cap(10), cont(0) {}

ListaCoches::ListaCoches(Coche* elems, int cont) : elems(elems), cap(cont + 10), cont(cont) {}

bool ListaCoches::cargarCoches() {
	std::ifstream in;
	in.open("coches.txt");
	if (!in.is_open()) return false;
	else {
		int n;
		in >> n;
		elems = new Coche[n];
		cont = n;
		cap = cont + 10;

		int i = 0;
		int code = 0, price = 0; std::string model = "";
		while (i < n) {
			in >> code;
			in >> price;
			in.get();
			getline(in, model);
			elems[i] = Coche(code, price, model);
			i++;
		}
	}

	in.close();
	return true;
}

Coche* ListaCoches::buscarCoche(int code) {
	Coche* car = nullptr;

	int i = 0;
	bool found = false;
	while (!found && i < cont) {
		if (elems[i].getCode() == code) {
			car = &elems[i];
			found = false;
		}
		i++;
	}

	return car;
}