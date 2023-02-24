#include "DisableOnEXit.h"
void DisableOnExit::initComponent() {
	myTr = ent_->getComponent<Transform>(_TRANSFORM);
}

void DisableOnExit::update() {
	Vector2D position = myTr->getPosition();
	if (position.getX() < 0 || position.getX() >= WIN_WIDTH || position.getY() < 0 || position.getY() >= WIN_HEIGHT) {
		ent_->setAlive(false);
	}
}