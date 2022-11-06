// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once

#include "Block.h"
#include "checkML.h"

typedef unsigned int uint;

class BlocksMap {
private:
	Block*** map;
	uint w, h, r, c;
	uint nBlocks;

public:
	BlocksMap(uint _w, uint _h, Texture* _texture, string filename);
	~BlocksMap();
	
	void loadMap(uint _w, uint _h, Texture* _texture, string filename);
	void render();
	int getBlocks();
	bool collidesB(SDL_Rect rectBall, Vector2D& collisionVector);
};