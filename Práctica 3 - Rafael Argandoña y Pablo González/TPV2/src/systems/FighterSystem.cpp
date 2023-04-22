#include "FighterSystem.h"
#include "../ecs/Manager.h"
#include "NetworkSystem.h"

// Recibir mensajes
void FighterSystem::receive(const Message& m) {
	switch (m.id) {
		// Si se ha acabado la ronda
		case _m_ROUND_OVER:
			onRoundOver();
			break;
	}
}

void FighterSystem::initSystem() {
	// Inicializa las variables para el cooldown de disparo y el de sonido de movimiento
	cooldown = 0; lastSoundTime = 0;
	startTime = soundTime = sdlutils().currRealTime();
	// Pillamos los componentes
	tr = mngr->getComponent<Transform>(mngr->getHandler(_hdlr_FIGHTER));
	fc = mngr->addComponent<FighterCtrl>(mngr->getHandler(_hdlr_FIGHTER), tr->getRotation());
}

void FighterSystem::update() {
	// Actualizamoss lo contadores
	cooldown = sdlutils().currRealTime() - startTime;
	lastSoundTime = sdlutils().currRealTime() - soundTime;

	// Si ha pulsado la flecha izquierda rotamos la nave hacia la izquierda
	if (InputHandler::instance()->isKeyDown(SDLK_LEFT)) {
		int r = (fc->getRot() - 2) % 360;
		fc->setRot(r); tr->setRotation(r);
		// MANDAR NUEVA ROTACION AL ONLINE SYSTEM, Q LA PASA AL OTRO PORTATIL
		Message mes;
		mes.id = _m_I_ROTATED;
		mes.my_data.sign = 0;
		mngr->send(mes);
	}
	// Si ha pulsado la flecha derecha rotamos la nave hacia la derecha
	else if (InputHandler::instance()->isKeyDown(SDLK_RIGHT)) {
		int r = (fc->getRot() + 2) % 360;
		fc->setRot(r); tr->setRotation(r);
		// MANDAR NUEVA ROTACION AL ONLINE SYSTEM, Q LA PASA AL OTRO PORTATIL
		Message mes;
		mes.id = _m_I_ROTATED;
		mes.my_data.sign = 1;
		mngr->send(mes);
	}

	// Si se ha pulsado hacia arriba
	if (InputHandler::instance()->isKeyDown(SDLK_UP)) setFighterVelocity();

	// Aumentamos el cooldown de disparo
	cooldown = sdlutils().currRealTime() - startTime;

	// Si se ha pulsado la tecla s
	if (InputHandler::instance()->isKeyDown(SDLK_s) && cooldown >= 250) {
		startTime = sdlutils().currRealTime();

		// QUE ESTE MENSAJE LO RECIBA EL ONLINE TAMBIEN
		Message m2;
		m2.id = _m_CREATE_BULLET;
		m2.bullet_data.layer = _grp_BULLETS;
		mngr->send(m2);
	}

	// Desacelerar
	tr->setVelocity(deAccelerate(tr->getVelocity()));

	// Aplicar cálculos
	tr->setPosition(tr->getPosition() + tr->getVelocity());

	// Cambiar de lado si se sale la nave
	showAtOppositeSide(tr);
}

// Movimiento de la nave
void FighterSystem::setFighterVelocity() {
	// Reproducir sonido
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

	// SE MANDA UN MENSAJE AL ONLINE SYSTEM PARA Q ESE MANDE LA INFORMACION DEL NUEVO VECTOR VEL AL OTRO PORTATIL
}

// Deacelerar la nave
Vector2D FighterSystem::deAccelerate(Vector2D vel) {
	Vector2D newVel = vel;
	// Si la nave tiene una magnitud mayor que 0.05, la decrecemos
	if (vel.magnitude() >= 0.05) {
		newVel = vel * 0.995;
		// Si ahora es menor, la seteamos a 0;
		if (newVel.magnitude() <= 0.05) newVel = Vector2D();
	}
	// Devolvemos la nueva velocidad
	return newVel;
}

// Mostrar en el lado contrario al salir de la pantalla
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

// Al acabar la ronda
void FighterSystem::onRoundOver() {
	// Devolvemos la nave al estado inicial del juego (sin velocidad ni rotacion y en el medio de la pantalla)
	Transform* plTr = mngr->getComponent<Transform>(mngr->getHandler(_hdlr_FIGHTER));
	plTr->setPosition(PLAYER_INITIAL_POS);
	plTr->setVelocity(Vector2D());
	plTr->setRotation(0);
	mngr->getComponent<FighterCtrl>(mngr->getHandler(_hdlr_FIGHTER))->setRot(0);
}

// Al empezar la ronda
void FighterSystem::onRoundStart() {
}