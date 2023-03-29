#include "FighterSystem.h"
#include "../ecs/Manager.h"

void FighterSystem::receive(const Message& m) {

}

void FighterSystem::initSystem() {
	Entity* f = mngr->addEntity();

	mngr->addComponent<Transform>(f, PLAYER_INITIAL_POS, PLAYER_WIDTH, PLAYER_HEIGHT);
	mngr->addComponent<FighterCtrl>(f);
	mngr->addComponent<DeAcceleration>(f);
	mngr->addComponent<ShowAtOppositeSide>(f);
	mngr->addComponent<Gun>(f);
	mngr->addComponent<Health>(f, &sdlutils().images().at(HEART));

	mngr->setHandler(_hdlr_FIGHTER, f);

	onRoundStart();
}

void FighterSystem::update() {
	cooldown = sdlutils().currRealTime() - startTime;
	Transform* tr = mngr->getComponent<Transform>(mngr->getHandler(_hdlr_FIGHTER));
	auto fc = mngr->getComponent<FighterCtrl>(mngr->getHandler(_hdlr_FIGHTER));

	// Si ha pulsado la flecha izquierda rotamos la nave hacia la izquierda
	if (InputHandler::instance()->isKeyDown(SDLK_LEFT)) {
		int r = (fc->getRot() - 2) % 360;
		fc->setRot(r);
		tr->setRotation(r);
	}
	// Si ha pulsado la flecha derecha rotamos la nave hacia la derecha
	else if (InputHandler::instance()->isKeyDown(SDLK_RIGHT)) {
		int r = (fc->getRot() + 2) % 360;
		fc->setRot(r);
		tr->setRotation(r);
	}

	// Si se ha pulsado hacia arriba
	if (InputHandler::instance()->isKeyDown(SDLK_UP)) {
		//if (lastSoundTime >= 500) { sound->play(); startTime = sdlutils().currRealTime(); }

		// Calcular el vector velocidad
		Vector2D vel = tr->getVelocity() + Vector2D(0, -1).rotate(fc->getRot()) * fc->getThrust();

		// Si sobrepasa el limite de velocidad, restringirlo
		if (vel.magnitude() > fc->getSpeedLimit()) vel = vel.normalize() * fc->getSpeedLimit();

		// Setear la velocidad
		tr->setVelocity(vel);
	}

	if (InputHandler::instance()->isKeyDown(SDLK_s)) {
		// DISPARAR
	}
	//// Si se ha pulsado la tecla ESCAPE lanzamos el estado de pausa
	//if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
	//	game->getStateMachine()->pushState(new PauseState(game, myObj->getComponent<Health>()->checkLifes()));
	//}
}


void FighterSystem::onCollision_FighterAsteroid() {
	Transform* plTr = mngr->getComponent<Transform>(mngr->getHandler(_hdlr_FIGHTER));
	plTr->setPosition(PLAYER_INITIAL_POS);
	plTr->setVelocity(Vector2D());
	plTr->setRotation(0);
	mngr->getComponent<FighterCtrl>(mngr->getHandler(_hdlr_FIGHTER))->setRot(0);
}

void FighterSystem::onRoundOver() {
}

void FighterSystem::onRoundStart() {
}