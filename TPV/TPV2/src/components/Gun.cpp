#include "Gun.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/VirtualTimer.h"

void Gun::initComponent() {
	tr = myObj->getComponent<Transform>();
}

void Gun::update() {
	handleInput();
}

void Gun::handleInput() {
	if (InputHandler::instance()->isKeyDown(SDLK_s)) {

	}
}