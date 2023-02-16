#pragma once

#include "Transform.h"

class DeAcceleration : public Component {
private:
	Transform* tr;
public:
	DeAcceleration() : Component() { } 

	//Metodos virtuales
	virtual void initComponent() {
		tr = ent_->getComponent<Transform>(_TRANSFORM);
	}

	// Decelera la nave en cada iteración bajando la velocidad un 0.005%
	virtual void update() {
		float newVelocity = tr->getVelocity();
		newVelocity *= 0.995;
		if (newVelocity <= 0.05) newVelocity = 0;
		tr->setVelocity(newVelocity);
	}
};