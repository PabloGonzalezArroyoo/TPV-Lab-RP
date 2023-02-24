#include "Gun.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/VirtualTimer.h"

void Gun::initComponent() {
	tr = ent_->getComponent<Transform>(_TRANSFORM);
}

void Gun::update() {
	handleInput();
}

void Gun::handleInput() {
	if (InputHandler::instance()->isKeyDown(SDLK_s)) {

	}
}