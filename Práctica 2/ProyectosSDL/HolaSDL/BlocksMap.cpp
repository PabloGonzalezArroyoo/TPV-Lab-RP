// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#include "BlocksMap.h"
#include <iostream>
#include <fstream>

const uint WALL_WIDTH = 15;

BlocksMap::BlocksMap(uint _w, uint _h, Texture* _texture, string filename) {
	loadMap(_w, _h, _texture, filename);
}

// Carga un mapa de un archivo
void BlocksMap::loadMap(uint _w, uint _h, Texture* _texture, string filename) {
	h = _h; w = _w;							// Ocupa la mitad superior de la pantalla
	nBlocks = 0;							// Inicializar nº de bloques a 0

	int aux, cols, rows; 
	ifstream in;							// Archivo de lectura
	in.open(filename + ".dat");
	if (!in.is_open()) throw string("Error: couldn't load map (" + filename + ")"); // Si no se ha encontrado el archivo
	in >> rows >> cols;						// Leer filas y columnas de la primera linea y guardar el tamaño
	if (rows <= 0 || cols <= 0) throw string("Error: columns or rows can't be equal or lower to 0 (" + filename + ")"); // Si no se han introducido valores correctos de r y c
	r = rows; c = cols;

	// Crear el array de arrays dinámico
	map = new Block**[r];					// Creamos las filas (array dentro de map***)	
	for (int i = 0; i < c; i++) map[i] = new Block*[c]; // Creamos las columnas (array dentro de las Block**[rows])
	
	// Recorremos el array bidimensional creando bloques y asignándolos a cada celda
	for (int j = 0; j < r; j++) {
		for (int k = 0; k < c; k++) {
			in >> aux;						// Se lee el color
			if (aux != 0) {					// Si tiene color (distinto de 0), hay un bloque
				map[j][k] = new Block(
					Vector2D(k * w / c + WALL_WIDTH, j * h / r + WALL_WIDTH), // Calculamos su posición en pantalla respecto a la posición en el array
					w / c,													// Hacemos que el ancho del bloque sea proporcional al ancho del mapa
					h / r,													// Hacemos que el alto del bloque sea proporcional al alto del mapa
					aux,													// Le pasamos su color
					_texture);												// Le pasamos el puntero a su textura
				nBlocks++;					// Aumentar contador de bloques
			}
			else map[j][k] = nullptr;										// Si no tiene color, no hay bloque
		}
	}

	in.close();								// Cerrar archivo
}

// Destructora - eleminamos punteros y memoria dinámica
BlocksMap::~BlocksMap() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			delete(map[i][j]);				// Borramos cada puntero de la matriz
		}
		delete[] map[i];					// Borramos los arrays de cada columna
	}
	delete[] map;							// Borramos el array de filas
}

// Llamamos al render de cada bloque dentro del mapa
void BlocksMap::render() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) if (map[i][j] != nullptr) map[i][j]->render();
	}
}

// Devuelve el nº de bloques actuales
int BlocksMap::getBlocks() {
	return nBlocks;
}

// Comprobar colisiones
bool BlocksMap::collidesB(SDL_Rect rectBall, Vector2D& collisionVector) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			// Comprobar si hay un bloque y la bola ha colisionado con él
			if (map[i][j] != nullptr && map[i][j]->collides(rectBall, collisionVector)) {
				map[i][j] = nullptr;		// Eliminar el bloque
				--nBlocks;					// Disminuir el nº de bloques
				return true;				// Confirmar colisión
			}
		}
	}
	return false;							// Negar colision
}

void BlocksMap::loadFromFile(istream in) {
	ArkanoidObject(in);
}

void BlocksMap::saveToFile(ostream out) {
	ArkanoidObject(out);
}