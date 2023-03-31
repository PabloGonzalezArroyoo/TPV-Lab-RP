#include "FighterSystem.h"
#include "../ecs/Manager.h"

void FighterSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_ROUND_OVER:
			onRoundOver();
			break;
	}
}

void FighterSystem::initSystem() {
	cooldown = 0; lastSoundTime = 0;
	startTime = soundTime = sdlutils().currRealTime();

	onRoundStart();
}

void FighterSystem::update() {
	cooldown = sdlutils().currRealTime() - startTime;
	lastSoundTime = sdlutils().currRealTime() - soundTime;

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
		setFighterVelocity(tr, fc);
	}

	// Aumentamos el cooldown de disparo
	cooldown = sdlutils().currRealTime() - startTime;

	// Si se ha pulsado el espacio
	if (InputHandler::instance()->isKeyDown(SDLK_s) && cooldown >= 250) {
		startTime = sdlutils().currRealTime();

		Message m1;
		m1.id = _m_PLAY_SOUND;
		m1._sound_data.sound = &sdlutils().soundEffects().at(FIRESFX);
		mngr->send(m1);

		Message m2;
		m2.id = _m_CREATE_BULLET;
		mngr->send(m2);
	}

	// Desacelerar
	tr->setVelocity(deAccelerate(tr->getVelocity()));

	// Aplicar cálculos
	tr->setPosition(tr->getPosition() + tr->getVelocity());

	// Cambiar de lado si se sale la nave
	showAtOppositeSide(tr);
}

void FighterSystem::setFighterVelocity(Transform* tr, FighterCtrl* fc) {
	if (lastSoundTime >= 500) {
		Message m;
		m.id = _m_PLAY_SOUND;
		m._sound_data.sound = &sdlutils().soundEffects().at(THRUST);
		mngr->send(m);

		soundTime = sdlutils().currRealTime(); 
	}

	// Calcular el vector velocidad
	Vector2D vel = tr->getVelocity() + Vector2D(0, -1).rotate(fc->getRot()) * fc->getThrust();

	// Si sobrepasa el limite de velocidad, restringirlo
	if (vel.magnitude() > fc->getSpeedLimit()) vel = vel.normalize() * fc->getSpeedLimit();

	// Setear la velocidad
	tr->setVelocity(vel);
}

Vector2D FighterSystem::deAccelerate(Vector2D vel) {
	Vector2D newVel = vel;
	if (vel.magnitude() >= 0.05) {
		newVel = vel * 0.995;

		if (newVel.magnitude() <= 0.05) newVel = Vector2D();
	}
	
	return newVel;
}

void FighterSystem::showAtOppositeSide(Transform* tr) {
	// Si se ha salido por la derecha
	if (tr->getPosition().getX() > WIN_WIDTH)
		tr->setPosition(Vector2D(0 - tr->getWidth(), tr->getPosition().getY()));

	// Si se ha salido por la izquierda
	else if (tr->getPosition().getX() < 0 - tr->getWidth())
		tr->setPosition(Vector2D(WIN_WIDTH, tr->getPosition().getY()));

	// Si se ha salido por arriba
	else if (tr->getPosition().getY() < 0 - tr->getHeight())
		tr->setPosition(Vector2D(tr->getPosition().getX(), WIN_HEIGHT));

	// Si se ha salido por abajo
	else if (tr->getPosition().getY() > WIN_HEIGHT)
		tr->setPosition(Vector2D(tr->getPosition().getX(), 0 - tr->getHeight()));
}

void FighterSystem::onCollision_FighterAsteroid() {
	Transform* plTr = mngr->getComponent<Transform>(mngr->getHandler(_hdlr_FIGHTER));
	plTr->setPosition(PLAYER_INITIAL_POS);
	plTr->setVelocity(Vector2D());
	plTr->setRotation(0);
	mngr->getComponent<FighterCtrl>(mngr->getHandler(_hdlr_FIGHTER))->setRot(0);
}

void FighterSystem::onRoundOver() {
	mngr->getComponent<Transform>(mngr->getHandler(_hdlr_FIGHTER))->setPosition(PLAYER_INITIAL_POS);
	mngr->getComponent<Transform>(mngr->getHandler(_hdlr_FIGHTER))->setRotation(0);
	mngr->getComponent<Transform>(mngr->getHandler(_hdlr_FIGHTER))->setVelocity(Vector2D());
	mngr->getComponent<FighterCtrl>(mngr->getHandler(_hdlr_FIGHTER))->setRot(0);
}

void FighterSystem::onRoundStart() {
	Entity* player = mngr->getHandler(_hdlr_FIGHTER);
	mngr->addComponent<FighterCtrl>(player);
}