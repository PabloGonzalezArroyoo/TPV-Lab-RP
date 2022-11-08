#include "ArkanoidObject.h"

ArkanoidObject::ArkanoidObject() {
	pos = Vector2D();
	w = h = 1;
	texture = nullptr;
}

ArkanoidObject::ArkanoidObject(Vector2D _pos, uint _width, uint _height, Texture* _texture) {
	pos = _pos;
	w = _width;
	h = _height;
	texture = _texture;
}

void ArkanoidObject::render() {
	texture->render(getRect());
}

SDL_Rect ArkanoidObject::getRect() {
	SDL_Rect dest;
	dest.x = (int)pos.getX(); dest.y = (int)pos.getY();
	dest.w = w; dest.h = h;
	return dest;
}