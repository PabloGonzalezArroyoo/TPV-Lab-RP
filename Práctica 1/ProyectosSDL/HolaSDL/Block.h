#pragma once

#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Block
{
private:
	Vector2D posAbs;
	uint w, h;
	uint color;
	Texture* texture;

public: 
	Block() { posAbs = Vector2D(); w = h = 0; color = 1; texture = nullptr; };
	Block(Vector2D _posAbs, uint _w, uint _h, uint _color, Texture* _texture);
	~Block();

	void render();
	bool collides(SDL_Rect rectBall, Vector2D& collisionVector);
	SDL_Rect getDestRect();
};

