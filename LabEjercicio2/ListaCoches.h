#pragma once

#include "Coche.h"

class ListaCoches
{
private:
	Coche* elems;
	int cap;
	int cont;
public:
	ListaCoches();
	ListaCoches(Coche* elems, int cont);
	bool cargarCoches();
	Coche* buscarCoche(int code);
};

