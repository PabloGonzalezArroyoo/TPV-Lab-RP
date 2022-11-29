// Pr�ctica 1: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#include "BlocksMap.h"
#include <iostream>
#include <fstream>

// Constructora
BlocksMap::BlocksMap(uint _w, uint _h, Texture* _texture, istream& in) {
	loadMap(_w, _h, _texture, in);
}

// Carga un mapa de un archivo
void BlocksMap::loadMap(uint _w, uint _h, Texture* _texture, istream& in) {
	h = _h; w = _w;							// Ocupa la mitad superior de la pantalla
	nBlocks = 0;							// Inicializar n� de bloques a 0

	int aux, cols, rows; 
	in >> rows >> cols;						// Leer filas y columnas de la primera linea y guardar el tama�o
	if (rows <= 0 || cols <= 0) throw FileFormatError("Columns or rows can't be equal or lower to 0 [(r, c) = (" + rows + cols); // Si no se han introducido valores correctos de r y c
	r = rows; c = cols;

	// Crear el array de arrays din�mico
	map = new Block**[r];					// Creamos las filas (array dentro de map***)	
	for (int i = 0; i < c; i++) map[i] = new Block*[c]; // Creamos las columnas (array dentro de las Block**[rows])
	
	// Recorremos el array bidimensional creando bloques y asign�ndolos a cada celda
	for (int j = 0; j < r; j++) {
		for (int k = 0; k < c; k++) {
			in >> aux;						// Se lee el color
			// if (aux < 0 || )
			if (aux != 0) {					// Si tiene color (distinto de 0), hay un bloque
				map[j][k] = new Block(
					Vector2D(k * w / c + WALL_WIDTH, j * h / r + WALL_WIDTH), // Calculamos su posici�n en pantalla respecto a la posici�n en el array
					w / c,													// Hacemos que el ancho del bloque sea proporcional al ancho del mapa
					h / r,													// Hacemos que el alto del bloque sea proporcional al alto del mapa
					aux,													// Le pasamos su color
					_texture);												// Le pasamos el puntero a su textura
				nBlocks++;					// Aumentar contador de bloques
			}
			else map[j][k] = nullptr;										// Si no tiene color, no hay bloque
		}
	}
}

// Destructora - eleminamos punteros y memoria din�mica
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

// Devuelve el n� de bloques actuales
int BlocksMap::getBlocks() {
	return nBlocks;
}

// Comprobar colisiones
bool BlocksMap::collides(SDL_Rect rectBall, Vector2D& collisionVector) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			// Comprobar si hay un bloque y la bola ha colisionado con �l
			if (map[i][j] != nullptr && map[i][j]->collides(rectBall, collisionVector)) {
				bDestroyed = map[i][j]->getPosition();
				map[i][j] = nullptr;		// Eliminar el bloque
				delete(map[i][j]);			// Eliminar el bloque
				--nBlocks;					// Disminuir el n� de bloques
				return true;				// Confirmar colisi�n
			}
		}
	}
	return false;							// Negar colision
}

// Guardar en archivo
void BlocksMap::saveToFile(ostream& out) {
	out << r << " " << c << endl;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] == nullptr) out << 0 << " ";
			else out << map[i][j]->getColor() << " ";
		}
		out << endl;
	}
}