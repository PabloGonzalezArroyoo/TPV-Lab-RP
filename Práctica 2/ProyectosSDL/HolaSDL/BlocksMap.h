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

public:
	BlocksMap(uint _w, uint _h, Texture* _texture, string filename);
	~BlocksMap();
	
	void loadMap(uint _w, uint _h, Texture* _texture, string filename);
	virtual void render();
	int getBlocks();
	bool collidesB(SDL_Rect rectBall, Vector2D& collisionVector);

	virtual void loadFromFile(istream in);
	virtual void saveToFile(ostream out);
};