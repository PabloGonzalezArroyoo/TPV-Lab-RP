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

public:
	Paddle() { pos = vel = Vector2D(); w = h = 0; texture = nullptr; };
	Paddle(Vector2D v, int width, int height, Vector2D velocity, Texture* txt);
	~Paddle();

	void render();
	void update(int dir);
	void handleEvents(SDL_Event e);
	void collision();
};