#include "Transform.h"

// Constructora vacía
Transform::Transform() : Component(), pos(Vector2D(0,0)), dir(Vector2D(0,0)), velocity(1) { }

// Constructora
Transform::Transform(Vector2D _pos, Vector2D _dir, float _vel, Vector2D _scale) :
	Component(), pos(_pos), dir(_dir), velocity(_vel), scale(_scale) { }

// Muve la nave sumando a la posición la velocidad por la dirección
void Transform::translate() {
	pos = pos + (dir * velocity);
}