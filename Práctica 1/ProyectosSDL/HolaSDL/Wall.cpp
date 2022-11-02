#include "Wall.h"
#include <iostream>

// Constructora
Wall::Wall(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _colVector) {
	pos = _pos;
	w = _w;
	h = _h;
	texture = _texture;
	colVector = _colVector;
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