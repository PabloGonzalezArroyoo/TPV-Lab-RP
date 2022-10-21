#pragma once

#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Block
{
private:
	Vector2D posAbs;
	uint w, h, r, c;
	uint color;
	Texture* texture;

public: 
	Block() { posAbs = Vector2D(); w = h = 0; r = c = 0; color = 1; texture = nullptr; };
	Block(Vector2D vector, uint width, uint height, uint rows, uint cols, uint colour, Texture* txt);
	~Block();

	void render();
};

