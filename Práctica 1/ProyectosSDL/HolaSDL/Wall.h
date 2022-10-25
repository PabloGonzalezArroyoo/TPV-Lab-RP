#pragma once

#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Wall
{
private:
	Vector2D pos = Vector2D();
	uint w = 0, h = 0;
	Texture* texture = nullptr;
	Vector2D colVector;

public:
	// Constructora y destructor
	Wall() { pos = Vector2D(); w = 0, h = 0; texture = nullptr; colVector = Vector2D(0, 0); };
	Wall(Vector2D v, uint w, uint h, Texture* txt, Vector2D colV);
	// Wall(Vector2D v, uint w, uint h, Texture* txt) : pos(v), w(w), h(h), texture(txt) {};
	~Wall();

	// Renderizado
	void render();
	bool collides(SDL_Rect rectBall, Vector2D& colV);
	SDL_Rect getDestRect();
};

