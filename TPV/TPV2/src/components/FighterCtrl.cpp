#include "FighterCtrl.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"

void FighterCtrl::initComponent() {
	tr = myObj->getComponent<Transform>();
}

void FighterCtrl::update() {
	handleInput();
}

void FighterCtrl::handleInput() {
	if (InputHandler::instance()->isKeyDown(SDLK_LEFT)) {
		r = (r - 5) % 360;
		tr->setRotation(r);
	}
	else if (InputHandler::instance()->isKeyDown(SDLK_RIGHT)) {
		r = (r + 5) % 360;
		tr->setRotation(r);
	}
	
	if (InputHandler::instance()->isKeyDown(SDLK_UP)) {
		Vector2D vel = tr->getVelocity();
		Vector2D aux = Vector2D(0, -1).rotate(r) * thrust;
		vel = vel + aux;
		if (vel.magnitude() > speedLimit) vel = vel.normalize() * speedLimit;
		tr->setVelocity(vel);
	}

	if (InputHandler::instance()->isKeyDown(SDLK_ESCAPE)) {
		
	}
}