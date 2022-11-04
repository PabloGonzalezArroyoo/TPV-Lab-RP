#pragma once

#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Game; // Para solucionar dependecia circular
class Ball {
private:
	Vector2D pos, vel;
	Texture* texture;
	Game* game;
	uint w, h;

public:
	Ball() { pos = vel = Vector2D(); texture = nullptr; w = h = 0; game = nullptr; };
	Ball(Vector2D _pos, Vector2D _vel, uint _w, uint _h, Texture* _texture, Game* _game);

	void render();
	void update();
	SDL_Rect getDestRect();
	Vector2D getVelocity() { return vel; };
	void setPosition(Vector2D _pos, Vector2D _vel);
};