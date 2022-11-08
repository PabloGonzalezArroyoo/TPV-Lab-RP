#include "MovingObject.h"


MovingObject::MovingObject(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel)
{}

void MovingObject::SetPosition(Vector2D _pos, Vector2D _vel) {
	pos = _pos;
	vel = _vel;
}