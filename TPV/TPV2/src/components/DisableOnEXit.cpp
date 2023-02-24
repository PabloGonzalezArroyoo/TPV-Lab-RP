#include "DisableOnExit.h"
#include "../ecs/Entity.h"

void DisableOnExit::initComponent() {
	myTr = myObj->getComponent<Transform>();
}

void DisableOnExit::update() {
	Vector2D position = myTr->getPosition();
	if (position.getX() < 0 || position.getX() >= WIN_WIDTH || position.getY() < 0 || position.getY() >= WIN_HEIGHT) {
		myObj->setAlive(false);
	}
}