#pragma once

#include "Alquiler.h"
#include "ListaCoches.h"

class ListaAlquileres
{
private: 
	Alquiler* elems;
	int cap;
	int cont;
public:
	ListaAlquileres();
	ListaAlquileres(Alquiler* elems, int cont);
	bool leerAlquileres(ListaCoches lc);
	void ordenaAlquileres();
	void mostrarAlquileres();
};

