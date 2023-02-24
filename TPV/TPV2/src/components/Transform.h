#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Transform : public Component {
private:
	Vector2D pos;
	Vector2D dir;
	float velocity;
	Vector2D scale;

public:
	// Constructoras
	Transform();
	Transform(Vector2D _pos, Vector2D _dir, float _vel, Vector2D _scale);

	// Movimiento
	void translate();

	// Setters
	void setPosition(Vector2D _pos) { pos = _pos; };
	void setDirection(Vector2D _dir) { dir = _dir; };
	void setVelocity(float _vel) { velocity = _vel; };
	void setScale(Vector2D _scale) { scale = _scale; }

	// Getters
	Vector2D getPosition() { return pos; };
	Vector2D getDirection() { return dir; };
	float getVelocity() { return velocity; };
	Vector2D getScale() { return scale; };
};