#include "FighterCtrl.h"
#include "../sdlutils/InputHandler.h"

void FighterCtrl::initComponent() {
	tr = ent_->getComponent<Transform>(_TRANSFORM);
}

void FighterCtrl::update() {
	handleInput();
}

void FighterCtrl::handleInput() {
	if (InputHandler::instance()->isKeyDown(SDLK_LEFT)) {

	}
	else if (InputHandler::instance()->isKeyDown(SDLK_RIGHT)) {

	}
	
	if (InputHandler::instance()->isKeyDown(SDLK_UP)) {
		tr->translate();
	}
}