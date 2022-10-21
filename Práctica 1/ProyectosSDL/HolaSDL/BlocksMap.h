#pragma once

#include "Block.h"

typedef unsigned int uint;

class BlocksMap
{
private:
	Block*** map;
	uint x, y, w, h, r, c;
	uint nBlocks;
	Block* collision;

public:
	BlocksMap(int width, int heigth, Texture* txt) { loadMap(width, heigth, txt); };
	~BlocksMap();
	
	void loadMap(int width, int heigth, Texture* txt);
	void render();
	int getBlocks();
	Vector2D getCollision();
};