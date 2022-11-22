#include "MovingObject.h"


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