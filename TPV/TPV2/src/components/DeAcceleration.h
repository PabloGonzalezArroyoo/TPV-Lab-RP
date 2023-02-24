#pragma once

#include "Transform.h"

class DeAcceleration : public Component {
private:
	Transform* tr;

public:
	DeAcceleration() : Component() { } 

	//Metodos virtuales
	virtual void initComponent() {
		tr = myObj->getComponent<Transform>();
	}

	// Decelera la nave en cada iteración bajando la velocidad un 0.005%
	virtual void update() {
		Vector2D newVelocity = tr->getVelocity();
		newVelocity = newVelocity * 0.995;
		if (newVelocity.getX() <= 0.05) newVelocity = 0;
		tr->setVelocity(newVelocity);
	}
};