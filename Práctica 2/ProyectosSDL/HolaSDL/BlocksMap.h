// Pr�ctica 1: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once

#include "ArkanoidObject.h"
#include "Block.h"

typedef unsigned int uint;

class BlocksMap : public ArkanoidObject{
private:
	Block*** map;
	uint r, c;
	uint nBlocks;
	Vector2D bDestroyed;

public:
	BlocksMap(uint _w, uint _h, Texture* _texture, istream& in);
	virtual ~BlocksMap();
	
	void loadMap(uint _w, uint _h, Texture* _texture, istream& in);
	int getBlocks();
	bool collidesB(SDL_Rect rectBall, Vector2D& collisionVector);
	Vector2D getDestroyedBlock() { return bDestroyed; }

	virtual void render();
	virtual void loadFromFile(istream& in);
	virtual void saveToFile(ostream& out);
};