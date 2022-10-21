#pragma once

#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Ball {
private:
	Vector2D pos, vel;
	Texture* texture;
	uint w, h;

public:
	Ball() { pos = vel = Vector2D(); texture = nullptr; w = h = 0; };
	Ball(Vector2D v, Vector2D velocity, uint width, uint height, Texture* txt);
	~Ball();

	void render();
	void update();
	void collision();
};