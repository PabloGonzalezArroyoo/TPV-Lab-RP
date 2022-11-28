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

void ArkanoidObject::loadFromFile(istream& in, Texture* _texture) {
	in >> w >> h;
	double newX, newY;
	in >> newX >> newY;
	pos = Vector2D(newX, newY);

	texture = _texture;
}

void ArkanoidObject::saveToFile(ostream& out) {
	out << w << " " << h << " " << pos.getX() << " " << pos.getY() << " ";
}