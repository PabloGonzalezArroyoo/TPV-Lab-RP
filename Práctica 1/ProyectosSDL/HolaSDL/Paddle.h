#pragma once

#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Paddle
{
private:
	Vector2D pos, vel;
	uint w, h;
	Texture* texture;
	Vector2D colVector;

public:
	Paddle() { pos = vel = colVector = Vector2D(); w = h = 0; texture = nullptr; };
	Paddle(Vector2D _pos, Vector2D _vel, uint _w, uint _h, Texture* _texture, Vector2D _colVector);
	~Paddle();

	void render();
	void update(int dir);
	void handleEvents(SDL_Event e);
	bool collidesP(SDL_Rect rectBall, Vector2D& collisionVector);
	SDL_Rect getDestRect();
};