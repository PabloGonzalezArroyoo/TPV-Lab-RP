#include "Wall.h"
#include <iostream>

// Constructora
Wall::Wall(Vector2D v, uint width, uint height, Texture* txt, Vector2D colV) {
	pos = v;
	w = width;
	h = height;
	texture = txt;
	colVector = colV;
}

// Destructora
Wall::~Wall() {
	pos.~Vector2D();
	w = h = 0;
	texture = nullptr;
}

// Renderizado
void Wall::render() {
	texture->render(getDestRect());
}

bool Wall::collidesW(SDL_Rect rectBall, Vector2D& collisionVector) {
	collisionVector = colVector;
	return SDL_HasIntersection(&rectBall, &getDestRect());
}

SDL_Rect Wall::getDestRect() {
	SDL_Rect dest;
	dest.x = (int)pos.getX(); dest.y = (int)pos.getY();
	dest.w = w; dest.h = h;
	return dest;
}