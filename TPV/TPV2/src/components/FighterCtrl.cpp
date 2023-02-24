#include "FighterCtrl.h"
#include "../sdlutils/InputHandler.h"

void FighterCtrl::initComponent() {
	tr = myObj->getComponent<Transform>();
}

void FighterCtrl::update() {
	handleInput();
}

void FighterCtrl::handleInput() {
	if (InputHandler::instance()->isKeyDown(SDLK_LEFT)) {
		// TO-DO: rotar
	}
	else if (InputHandler::instance()->isKeyDown(SDLK_RIGHT)) {
		// TO-DO: rotar
	}
	
	if (InputHandler::instance()->isKeyDown(SDLK_UP)) {
		tr->translate();
	}
}