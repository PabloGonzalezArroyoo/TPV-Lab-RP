// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once

#include "MovingObject.h"

typedef unsigned int uint;
const uint MAX_WIDTH = 200, MIN_WIDTH = 50;

class Paddle : public MovingObject{
private:
	int dir;

public:
	// Constructoras
	Paddle() { pos = vel = Vector2D(); w = h = 0; texture = nullptr; dir = 0; };
	Paddle(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel);

	// M�todos esenciales
	virtual void update();
	virtual void handleEvent(SDL_Event e);
	virtual bool collides(SDL_Rect rectBall, Vector2D& collisionVector);

	// Efectos rewards
	void changeDimensions(bool elongate);
};