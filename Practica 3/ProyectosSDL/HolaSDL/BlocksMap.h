// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once

#include "Block.h"

typedef unsigned int uint;

// CLASE BLOCKSMAP - CONJUNTO DE OBJETOS DEL JUEGO (ARKANOID OBJECT)
// Propiedades:
//		- Heredada las de ArkanoidObject (w, h, texture, pos)
//		- map: el array bidimesional de punteros a bloques
//		- r y c: filas (r) y columnas (c)
//		- nBlock: n�mero total de bloques actuales en el mapa
//		- bDestroyed: posici�n del �ltimo bloque destruido
// M�todos:
//		Constructora		-> Sobrecargada y que recibe un archivo abierto del que leer la informacion del mapa (bloques -> posicion, color)
//		Destructora			-> Recorre el array bidimensional eliminando la memoria dinamica (punteros, columnas, filas)
//		collides			-> Recorre el array bidimensional comprobando si alguno de los bloques intersecta con la pelota, destuyendo el bloque,
//							actualizando el n�mero de bloques, confirmando la colisi�n y actualizando la bDestroyed
//		getBlocks			-> Devuelve el numero de bloques que contiene el mapa en tiempo de ejecucion
//		getDestroyedBlock	-> Devuelve el vector posicion del ultimo bloque destruido
//		loadMap				-> Reemplazo de: virtual void loadFromFile(istream& in)
//		saveToFile			-> guarda la informacion necesaria en un archivo abierto recibido como parametro

class BlocksMap : public ArkanoidObject{
private:
	Block*** map;
	uint r, c;
	uint nBlocks;
	Vector2D bDestroyed;

public:
	// Constructora y destructora
	BlocksMap(uint _w, uint _h, Texture* _texture, istream& in);
	virtual ~BlocksMap();

	// M�todos esenciales
	virtual bool collides(SDL_Rect rectBall, Vector2D& collisionVector);
	virtual void render();

	// Getters
	int getBlocks();
	Vector2D getDestroyedBlock() { return bDestroyed; }

	// Guardado y cargado
	void loadMap(uint _w, uint _h, Texture* _texture, istream& in);
	virtual void saveToFile(ostream& out);
};