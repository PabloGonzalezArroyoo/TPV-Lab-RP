#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

struct Transform : public Component {
protected:
	Vector2D pos, vel;
	int width, height;
	float rotation;

public:
	// ID
	constexpr static cmpId_type id = _TRANSFORM;

	// Constructoras
	Transform() : Component(), pos(Vector2D()), vel(Vector2D()), width(1), height(1), rotation(0) { }
	Transform(Vector2D _p, Vector2D _v, int _w, int _h, float _r) : 
			Component(), pos(_p), vel(_v), width(_w), height(_h), rotation(_r) { }

	// ----- GETTERS -----
	inline Vector2D getPosition() { return pos; };
	inline Vector2D getVelocity() { return vel; };
	inline float getRotation() { return rotation; }
	inline int getWidth() { return width; }
	inline int getHeight() { return height; }

	// ----- SETTERS -----
	inline void setPosition(Vector2D _pos) { pos = _pos; };
	inline void setVelocity(Vector2D _vel) { vel = _vel; };
	inline void setRotation(float _rotation) { rotation = _rotation; }
	inline void setWidth(int _width) { width = _width; }
	inline void setHeight(int _height) { height = _height; }
};