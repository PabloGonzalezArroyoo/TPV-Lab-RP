#include "DeAcceleration.h"
#include "../ecs/Entity.h"

void DeAcceleration::initComponent() {
	tr = myObj->getComponent<Transform>();
}

void DeAcceleration::update() {
	Vector2D newVelocity = tr->getVelocity();
	if (newVelocity.magnitude() >= 0.05) {
		newVelocity = newVelocity * 0.995;
		if (newVelocity.magnitude() <= 0.05) 
			newVelocity = Vector2D();
		tr->setVelocity(newVelocity);
	}
	tr->translate();
}