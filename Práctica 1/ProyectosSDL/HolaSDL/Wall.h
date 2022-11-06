// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"

typedef unsigned int uint;

class Wall {
private:
	Vector2D pos;
	uint w, h;
	Texture* texture;
	Vector2D colVector;

public:
	// Constructora y destructor
	Wall() { pos = Vector2D(); w = 0, h = 0; texture = nullptr; colVector = Vector2D(0, 0); };
	Wall(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _colVector);

	// Renderizado
	void render();
	bool collidesW(SDL_Rect rectBall, Vector2D& colV);
	SDL_Rect getDestRect();
};

