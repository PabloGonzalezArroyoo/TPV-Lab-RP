#include "GhostFighterSystem.h"
#include "NetworkSystem.h"

void GhostFighterSystem::initSystem() {
	// Crea la nave y le añade los componentes basicos
	Entity* f = mngr->addEntity(_grp_MULTIPLAYER);

	auto network = mngr->getSystem<NetworkSystem>();
	if (network) {

		if (!network->isHost()) tr = mngr->addComponent<Transform>(f, Vector2D(0, WIN_HEIGHT / 2 - PLAYER_HEIGHT / 2), PLAYER_WIDTH, PLAYER_HEIGHT, Vector2D(), 90);
		else tr = mngr->addComponent<Transform>(f, Vector2D(WIN_WIDTH - PLAYER_WIDTH, WIN_HEIGHT / 2 - PLAYER_HEIGHT / 2), PLAYER_WIDTH, PLAYER_HEIGHT, Vector2D(), -90);
	}

	mngr->addComponent<Health>(f, 1);
	fc = mngr->addComponent<FighterCtrl>(f, tr->getRotation());

	// Setea el handler de la nave
	mngr->setHandler(_hdlr_GHOST_FIGHTER, f);
}

void GhostFighterSystem::update() {	
	tr->setVelocity(deAccelerate(tr->getVelocity()));

	// Aplicar cálculos
	tr->setPosition(tr->getPosition() + tr->getVelocity());
	
	showAtOppositeSide(tr);
}

void GhostFighterSystem::applyRotation(int rot) {
	int r = (fc->getRot() + rot) % 360;
	tr->setRotation(r);
	fc->setRot(r);
}