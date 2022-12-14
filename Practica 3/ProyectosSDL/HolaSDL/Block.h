// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once

#include "ArkanoidObject.h"

typedef unsigned int uint;

class Block : public ArkanoidObject{
private:
	uint color;

public:
	// Constructoras
	Block() { pos = Vector2D(); w = h = 0; color = 1; texture = nullptr; };
	Block(Vector2D _pos, uint _w, uint _h, uint _color, Texture* _texture);

	// Métodos esenciales
	virtual void render();

	// Colisiones
	bool collides(SDL_Rect rectBall, Vector2D& collisionVector);

	// Getters
	uint getColor() { return color; }
	Vector2D getPosition() { return pos; }
};

