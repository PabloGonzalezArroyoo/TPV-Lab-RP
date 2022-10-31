#pragma once

#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Game;
class Ball {
private:
	Vector2D pos, vel;
	Texture* texture;
	Game* game;
	uint w, h;

public:
	Ball() { pos = vel = Vector2D(); texture = nullptr; w = h = 0; game = nullptr; };
	Ball(Vector2D v, Vector2D velocity, uint width, uint height, Texture* txt, Game* game);
	~Ball();

	void render();
	void update();
	void collision();
	SDL_Rect getDestRect();
	Vector2D getVelocity() { return vel; };
};