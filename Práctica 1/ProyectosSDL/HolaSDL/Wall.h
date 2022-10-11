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

public:
	// Constructora y destructor
	Wall();
	Wall(Vector2D v, uint w, uint h, Texture txt);
	~Wall();

	// Renderizado
	void render();
};

