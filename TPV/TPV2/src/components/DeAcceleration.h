#pragma once

#include "Transform.h"


class DeAcceleration : public Component {
private:
	Transform* tr;

public:
	static const int id = _DEACCELERATION;

	DeAcceleration() : Component() { } 

	//Metodos virtuales
	virtual void initComponent();

	// Decelera la nave en cada iteración bajando la velocidad un 0.005%
	virtual void update();
};