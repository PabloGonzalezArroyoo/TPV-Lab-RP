#include "Follow.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

void Follow::initComponent() {
	myTr = myObj->getComponent<Transform>();
	//Cojo el Transform del player
	plTr = myMng->getHandler(_hdlr_FIGHTER)->getComponent<Transform>();
}

void Follow::update() {
	Vector2D newVel = (plTr->getPosition() - myTr->getPosition()).normalize() * randomSpeed;
	myTr->setVelocity(newVel);
}