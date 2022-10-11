#include "Wall.h"

// Constructora
Wall::Wall(Vector2D v, uint width, uint height, Texture txt) {
	pos = v;
	w = width;
	h = height;
	texture = &txt;
}

// Destructora
Wall::~Wall() {
	pos.~Vector2D();
	w = h = 0;
	texture->wipe();
}

// Renderizado
void Wall::render() {
	SDL_Rect dest;
	dest.x = pos.getX(); dest.y = pos.getY();
	dest.w = w; dest.h = h;

	texture->render(dest);
}