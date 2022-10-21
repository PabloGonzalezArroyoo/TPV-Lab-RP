#include "Wall.h"
#include <iostream>

// Constructora
Wall::Wall(Vector2D v, uint width, uint height, Texture* txt) {
	pos = v;
	w = width;
	h = height;
	texture = txt;
}

// Destructora
Wall::~Wall() {
	pos.~Vector2D();
	w = h = 0;
	texture->wipe();
	delete(texture);
}

// Renderizado
void Wall::render() {
	SDL_Rect dest;
	dest.x = (int) pos.getX(); dest.y = (int) pos.getY();
	dest.w = w; dest.h = h;
	texture->render(dest);
}