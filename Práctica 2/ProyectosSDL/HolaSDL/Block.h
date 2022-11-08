// Pr�ctica 1: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once

#include "ArkanoidObject.h"

typedef unsigned int uint;

class Block : public ArkanoidObject{
private:
	uint color;

public: 
	Block() { pos = Vector2D(); w = h = 0; color = 1; texture = nullptr; };
	Block(Vector2D _pos, uint _w, uint _h, uint _color, Texture* _texture);

	virtual void render();
	bool collides(SDL_Rect rectBall, Vector2D& collisionVector);
};

