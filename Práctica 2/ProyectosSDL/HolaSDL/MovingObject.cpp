#include "MovingObject.h"

MovingObject::MovingObject() : ArkanoidObject(), vel(Vector2D(0,0)) {}

MovingObject::MovingObject(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel)
{
	pos = _pos;
	w = _w; h = _h;
	texture = _texture;
	vel = _vel;
}

void MovingObject::setPosition(Vector2D _pos, Vector2D _vel) {
	pos = _pos;
	vel = _vel;
}

void MovingObject::loadFromFile(istream& in, Texture* _texture) {
	ArkanoidObject::loadFromFile(in, _texture);

	double velX, velY;
	in >> velX >> velY;
	vel = Vector2D(velX, velY);
}

void MovingObject::saveToFile(ostream& out) {
	ArkanoidObject::saveToFile(out);
	out << vel.getX() << " " << vel.getY() << " ";
}