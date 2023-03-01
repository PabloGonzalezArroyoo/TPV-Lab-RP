#include "Gun.h"
#include "../sdlutils/InputHandler.h"
#include "Image.h"
#include "DisableOnEXit.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

void Gun::initComponent() {
	tr = myObj->getComponent<Transform>();
}

void Gun::update() {
	handleInput();
}

void Gun::handleInput() {
	lastShotTime = SDLUtils::instance()->currRealTime() - startTime;
	if (InputHandler::instance()->isKeyDown(SDLK_s) && lastShotTime >= 250) {
		startTime = SDLUtils::instance()->currRealTime();
		Entity* b = myMng->addEntity(_grp_BULLETS);
		b->addComponent<Transform>(bulletPos(), bulletVel(), BULLET_WIDTH, BULLET_HEIGTH, tr->getRotation());
		b->addComponent<Image>(game->getTexture(FIRE));
		b->addComponent<DisableOnExit>();
	}
}

Vector2D Gun::bulletPos() {
	Vector2D bPos = tr->getPosition()
		+ Vector2D(tr->getWidth() / 2.0f, tr->getHeight() / 2.0f)
		- Vector2D(0.0f, tr->getHeight() / 2.0f + 5.0f + 12.0f).rotate(tr->getRotation())
		- Vector2D(2.0f, 10.0f);
	return bPos;
}

Vector2D Gun::bulletVel() {
	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(tr->getRotation()) * (tr->getVelocity().magnitude() + 5.0f);
	return bVel;
}