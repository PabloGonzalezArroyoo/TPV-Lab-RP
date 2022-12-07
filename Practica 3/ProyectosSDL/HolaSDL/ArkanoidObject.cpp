#include "ArkanoidObject.h"

// Constructora vac�a
ArkanoidObject::ArkanoidObject() {
	pos = Vector2D();
	w = h = 1;
	texture = nullptr;
}

// Constructora
ArkanoidObject::ArkanoidObject(Vector2D _pos, uint _width, uint _height, Texture* _texture) {
	pos = _pos;
	w = _width;
	h = _height;
	texture = _texture;
}

// Renderizado
void ArkanoidObject::render() {
	texture->render(getRect());
}

// Devuelve el rect�ngulo de representaci�n del objeto
SDL_Rect ArkanoidObject::getRect() {
	SDL_Rect dest;
	dest.x = (int)pos.getX(); dest.y = (int)pos.getY();
	dest.w = w; dest.h = h;
	return dest;
}

// Cargar de archivo
void ArkanoidObject::loadFromFile(istream& in, Texture* _texture) {
	in >> w >> h;
	double newX, newY;
	in >> newX >> newY;
	pos = Vector2D(newX, newY);

	texture = _texture;
}

// Guardar en archivo
void ArkanoidObject::saveToFile(ostream& out) {
	out << w << " " << h << " " << pos.getX() << " " << pos.getY() << " ";
}