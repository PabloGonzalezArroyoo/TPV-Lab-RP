#include "BlocksMap.h"
#include <iostream>
#include <fstream>

const uint BLOCK_WIDTH = 535;
const uint BLOCK_HEIGHT = 146;

void BlocksMap::loadMap(int width, int heigth, Texture* txt) {
	h = heigth / 2; w = width;				// Ocupa la mitad superior de la pantalla
	nBlocks = 0;							// Inicializar nº de bloques a 0

	int rows, cols, aux;
	ifstream in;							// Archivo de lectura
	// El método deberá recibir el nombre de fichero
	in.open("level01.dat");
	if (!in.is_open()) cout << "Cagaste";
	in >> rows;	in >> cols;					// Leer filas y columnas de la primera linea
	r = rows; c = cols;						// Guardar tamaño del array

	cout << "c: " << c << " r: " << r << endl;
	// Crear el array de arrays dinámico
	map = new Block**[rows];				// Creamos las filas (array dentro de map***)	
	for (int i = 0; i < cols; i++) {		// Creamos las columnas (array dentro de las Block**[rows])
		map[i] = new Block*[cols];
	}
	
	// Recorremos el array bidimensional creando bloques y asignándolos a cada celda
	for (int j = 0; j < r; j++) {
		for (int k = 0; k < c; k++) {
			in >> aux;						// Se lee el color
			if (aux != 0) {					// Si tiene color (distinto de 0), hay un bloque
				map[j][k] = new Block(Vector2D(j * BLOCK_WIDTH / r, k * BLOCK_HEIGHT / c), w / rows, h / cols, aux, txt);
				nBlocks++;					// Aumnetar contador de bloques
				cout << nBlocks << " - ";
			}
			else map[j][k] = nullptr;
		}
	}

	in.close();
}

void BlocksMap::render() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] != nullptr) map[i][j]->render();
		}
	}
}

int BlocksMap::getBlocks() {
	return nBlocks;
}

Vector2D BlocksMap::getCollision() {
	return Vector2D();
}