// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once

#include "MovingObject.h"

typedef unsigned int uint;

class Paddle : public MovingObject{

public:
	Paddle() { pos = vel = Vector2D(); w = h = 0; texture = nullptr; };
	Paddle(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel);

	virtual void update(int dir, uint const& winW, uint const& wallW);
	virtual void handleEvents(SDL_Event e, uint const& winW, uint const& wallW);
	bool collidesP(SDL_Rect rectBall, Vector2D& collisionVector);
};