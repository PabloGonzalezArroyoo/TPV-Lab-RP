#include "ShowAtOppositeSide.h"
#include "../ecs/Entity.h"

void ShowAtOppositeSide::initComponent() {
	tr = myObj->getComponent<Transform>();
}

void ShowAtOppositeSide::update() {
	/*if (tr != nullptr) {
		if (tr->getPosition()->getX() > WIN_WIDTH) tr->setPosition(Vector2D(0, tr->getPosition()->getY()));
		else if (tr->getPosition()->getX() < 0) tr->setPosition(Vector2D(WIN_WIDTH, tr->getPosition()->getY()));
		else if (tr->getPosition()->getY() < 0) tr->setPosition(Vector2D(tr->getPosition()->getX(), 0));
		else if (tr->getPosition()->getY() > 0) tr->setPosition(Vector2D(tr->getPosition()->getX(), WIN_HEIGHT));
	}*/
}