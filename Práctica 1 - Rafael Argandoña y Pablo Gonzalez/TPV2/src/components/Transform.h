#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Transform : public Component {
private:
	// Variables de mi posicion, velocidad, dimensiones y rotacion
	Vector2D pos;
	Vector2D vel;
	int width;
	int height;
	float rotation;

public:
	// Id del componente
	constexpr static cmpId_type id = _TRANSFORM;

	// Constructoras
	Transform();
	Transform(Vector2D _pos, Vector2D _vel, int _width, int _height, float _rotation = 0);

	// Movimiento
	virtual void update();

	// Setters
	inline void setPosition(Vector2D _pos) { pos = _pos; };
	inline void setVelocity(Vector2D _vel) { vel = _vel; };
	inline void setRotation(float _rotation) { rotation = _rotation; }
	inline void setWidth(int _width) { width = _width; }
	inline void setHeight(int _height) { height = _height; }

	// Getters
	inline Vector2D getPosition() { return pos; };
	inline Vector2D getVelocity() { return vel; };
	inline float getRotation() { return rotation; }
	inline int getWidth() { return width; }
	inline int getHeight() { return height; }
};