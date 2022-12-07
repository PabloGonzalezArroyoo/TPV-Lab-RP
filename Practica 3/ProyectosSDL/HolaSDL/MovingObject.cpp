#include "MovingObject.h"

// Constructora vacía
MovingObject::MovingObject() : ArkanoidObject(), vel(Vector2D(0,0)) {}

// Constructora
MovingObject::MovingObject(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel)
{
	pos = _pos;
	w = _w; h = _h;
	texture = _texture;
	vel = _vel;
}

// Asigna la posicón y la velocidad a la recibida
void MovingObject::setPosition(Vector2D _pos, Vector2D _vel) {
	pos = _pos;
	vel = _vel;
}

// Cargar desde archivo
void MovingObject::loadFromFile(istream& in, Texture* _texture) {
	ArkanoidObject::loadFromFile(in, _texture);

	double velX, velY;
	in >> velX >> velY;
	vel = Vector2D(velX, velY);
}

// Guardar en archivo
void MovingObject::saveToFile(ostream& out) {
	ArkanoidObject::saveToFile(out);
	out << vel.getX() << " " << vel.getY() << " ";
}