#include "Follow.h"

void Follow::initComponent() {
	myTr = ent_->getComponent<Transform>(_TRANSFORM);
	//Cojo el Transform del player
}

void Follow::update() {
	Vector2D newVel = (myTr->getPosition() - plTr->getPosition()).normalize();
	myTr->setDirection(newVel);
}