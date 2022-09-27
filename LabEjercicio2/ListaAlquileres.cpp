#include "ListaAlquileres.h"

#include <iostream>
#include <fstream>
#include <algorithm>

ListaAlquileres::ListaAlquileres() : elems(), cap(10), cont(0) {}

ListaAlquileres::ListaAlquileres(Alquiler* elems, int cont) : elems(elems), cap(cont + 10), cont(cont) {}

bool ListaAlquileres::leerAlquileres(ListaCoches lc) {
	ifstream in;
	in.open("rent.txt");
	if (!in.is_open()) return false;
	else {
		int n;
		in >> n;
		elems = new Alquiler[n];
		cont = n;
		cap = cont + 10;

		int code = 0, days = 0; Date date;
		for (int i = 0; i < n; i++) {
			in >> code;
			in >> date;
			in.get();
			in >> days;

			elems[i] = Alquiler(lc.buscarCoche(code), date, days);
		}
	}

	in.close();
	return true;
}

/*void ListaAlquileres::ordenaAlquileres() {
	sort(&elems[0], &elems[cont]);
}*/

void ListaAlquileres::mostrarAlquileres() {
	for (int i = 0; i < cont; i++)
	{
		if (elems[i].getCoche() != nullptr) {
			elems[i].getDate().print();
			std::cout << " " << elems[i].getCoche()->getModel() << " " << elems[i].getDays() << " dia(s) por "
				<< elems[i].getCoche()->getPrice() * elems[i].getDays() << " euros " << endl;
		}
		else {
			elems[i].getDate().print();
			std::cout << " ERROR: Modelo inexistente" << endl;
		}
	}
}