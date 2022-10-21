#include "BlocksMap.h"
#include <iostream>
#include <fstream>

void BlocksMap::loadMap(int width, int heigth, Texture* txt) {
	h = heigth / 2; w = width;				// Ocupa la mitad superior de la pantalla

	int rows, cols, aux;
	ifstream in;							// Archivo de lectura
	// El m�todo deber� recibir el nombre de fichero
	in.open("level01.dat");
	in >> rows;	in >> cols;					// Leer filas y columnas de la primera linea
	r = rows; c = cols;						// Guardar tama�o del array

	// Crear el array de arrays din�mico
	map = new Block**[rows];				// Creamos las filas (array dentro de map***)	
	for (int i = 0; i < cols; i++) {		// Creamos las columnas (array dentro de las Block**[rows])
		map[i] = new Block*[cols];
	}
	
	// Recorremos el array bidimensional creando bloques y asign�ndolos a cada celda
	for (int j = 0; j < rows; j++) {
		for (int k = 0; j < cols; k++) {
			in >> aux;						// Se lee el color
			if (aux != 0) {					// Si tiene color (distinto de 0), hay un bloque
				Block b = Block(Vector2D(j, k), w/rows, h/cols, rows, cols, aux, txt); // Preguntar por la posici�n absoluta
				map[j][k] = &b;				// Asignar el bloque a la posici�n correspondiente (PROPONER NUEVO METODO GETBLOCKPTR)
				nBlocks++;					// Aumnetar contador de bloques
			}
		}
	}

	in.close();
}

void BlocksMap::render() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			map[i][j]->render();
		}
	}
}

int BlocksMap::getBlocks() {
	return nBlocks;
}

Vector2D BlocksMap::getCollision() {

}