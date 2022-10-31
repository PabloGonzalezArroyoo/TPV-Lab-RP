#pragma once

#include "Block.h"

typedef unsigned int uint;

class BlocksMap
{
private:
	Block*** map;
	uint x, y, w, h, r, c;
	uint nBlocks;

public:
	BlocksMap(int width, int heigth, Texture* txt, string filename) { loadMap(width, heigth, txt, filename); };
	~BlocksMap();
	
	void loadMap(int width, int heigth, Texture* txt, string filename);
	void render();
	int getBlocks();
	bool collidesB(SDL_Rect rectBall, Vector2D& collisionVector);
};