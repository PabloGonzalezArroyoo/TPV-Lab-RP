#include "BlocksMap.h"
#include <iostream>
#include <fstream>

const uint wallWidth = 15;

void BlocksMap::loadMap(int width, int heigth, Texture* txt, string filename) {
	h = heigth; w = width;					// Ocupa la mitad superior de la pantalla
	nBlocks = 0;							// Inicializar nº de bloques a 0

	int rows, cols, aux;
	ifstream in;							// Archivo de lectura
	in.open(filename + ".dat");
	if (!in.is_open()) cout << "ERROR";
	in >> rows;	in >> cols;					// Leer filas y columnas de la primera linea
	r = rows; c = cols;						// Guardar tamaño del array

	// Crear el array de arrays dinámico
	map = new Block**[rows];				// Creamos las filas (array dentro de map***)	
	for (int i = 0; i < cols; i++) map[i] = new Block*[cols]; // Creamos las columnas (array dentro de las Block**[rows])
	
	// Recorremos el array bidimensional creando bloques y asignándolos a cada celda
	for (int j = 0; j < rows; j++) {
		for (int k = 0; k < cols; k++) {
			in >> aux;						// Se lee el color
			if (aux != 0) {					// Si tiene color (distinto de 0), hay un bloque
				map[j][k] = new Block(Vector2D(k * w / cols + wallWidth, j * h / rows + wallWidth), w / cols, h / rows, aux, txt);
				nBlocks++;					// Aumentar contador de bloques
			}
			else map[j][k] = nullptr;
		}
	}

	in.close();
}

BlocksMap::~BlocksMap() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			delete(map[i][j]);
		}
		delete[] map[i];
	}
	delete[] map;
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

bool BlocksMap::collidesB(SDL_Rect rectBall, Vector2D& collisionVector) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] != nullptr && map[i][j]->collides(rectBall, collisionVector)) {
				map[i][j] = nullptr;
				--nBlocks;
				return true;
			}
		}
	}
	return false;
}