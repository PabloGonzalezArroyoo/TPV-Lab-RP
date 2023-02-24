#include "Transform.h"

// Constructora vac�a
Transform::Transform() : Component(), pos(Vector2D()), vel(Vector2D()), width(1), height(1), rotation(0) { }

// Constructora
Transform::Transform(Vector2D _pos, Vector2D _vel, int _width, int _height, float _rotation) :
	Component(), pos(_pos), vel(_vel), width(_width), height(_height), rotation(_rotation) { }

// Muve la nave sumando a la posici�n la velocidad por la direcci�n
void Transform::translate() {
	pos = pos + vel;
}