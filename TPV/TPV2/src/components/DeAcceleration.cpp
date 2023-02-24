#include "DeAcceleration.h"
#include "../ecs/Entity.h"

void DeAcceleration::initComponent() {
	tr = myObj->getComponent<Transform>();
}

void DeAcceleration::update() {
	Vector2D newVelocity = tr->getVelocity();
	newVelocity = newVelocity * 0.995;
	if (newVelocity.getX() <= 0.05) newVelocity = 0;
	tr->setVelocity(newVelocity);
}