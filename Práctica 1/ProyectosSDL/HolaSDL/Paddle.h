// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once

#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Paddle {
private:
	Vector2D pos, vel;
	uint w, h;
	Texture* texture;

public:
	Paddle() { pos = vel = Vector2D(); w = h = 0; texture = nullptr; };
	Paddle(Vector2D _pos, Vector2D _vel, uint _w, uint _h, Texture* _texture);

	void render();
	void update(int dir, uint const& winW, uint const& wallW);
	void handleEvents(SDL_Event e, uint const& winW, uint const& wallW);
	bool collidesP(SDL_Rect rectBall, Vector2D& collisionVector);
	void setPosition(Vector2D _pos, Vector2D _vel);
	SDL_Rect getDestRect();
};