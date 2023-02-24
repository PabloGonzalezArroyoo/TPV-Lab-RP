#include "Follow.h"

void Follow::initComponent() {
	myTr = myObj->getComponent<Transform>();
	//Cojo el Transform del player
}

void Follow::update() {
	Vector2D newVel = (myTr->getPosition() - plTr->getPosition()).normalize();
	myTr->setVelocity(newVel);
}