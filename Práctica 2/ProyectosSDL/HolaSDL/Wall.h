// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once

#include "ArkanoidObject.h"

typedef unsigned int uint;

class Wall : public ArkanoidObject{
private:
	Vector2D colVector;

public:
	// Constructora y destructor
	Wall() { pos = Vector2D(); w = 0, h = 0; texture = nullptr; colVector = Vector2D(0, 0); };
	Wall(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _colVector);

	// Renderizado
	virtual void render();
	bool collidesW(SDL_Rect rectBall, Vector2D& colV);
};

