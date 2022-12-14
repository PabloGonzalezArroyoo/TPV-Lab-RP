// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once

#include "Block.h"

typedef unsigned int uint;

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
	// virtual void loadFromFile(istream& in);
	virtual void saveToFile(ostream& out);
};