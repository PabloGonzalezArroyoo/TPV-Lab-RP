#include "GhostFighterSystem.h"
#include "NetworkSystem.h"

void GhostFighterSystem::initSystem() {
	// Crea la nave y le añade los componentes basicos
	Entity* f = mngr->addEntity(_grp_MULTIPLAYER);

	// Pillamos el sistema del online (para saber donde colocar la nave)
	auto network = mngr->getSystem<NetworkSystem>();
	if (!network->isHost()) tr = mngr->addComponent<Transform>(f, Vector2D(0, WIN_HEIGHT / 2 - PLAYER_HEIGHT / 2), PLAYER_WIDTH, PLAYER_HEIGHT, Vector2D(), 90);
	else tr = mngr->addComponent<Transform>(f, Vector2D(WIN_WIDTH - PLAYER_WIDTH, WIN_HEIGHT / 2 - PLAYER_HEIGHT / 2), PLAYER_WIDTH, PLAYER_HEIGHT, Vector2D(), -90);

	// Añadimos los ultimos componentes
	mngr->addComponent<Health>(f, 1);
	fc = mngr->addComponent<FighterCtrl>(f, tr->getRotation());

	// Setea el handler de la nave
	mngr->setHandler(_hdlr_GHOST_FIGHTER, f);
}

// Reaccionamos al mensaje de que se movio la nave
void GhostFighterSystem::receive(const Message& m) {
	if (m.id == _m_GHOST_MOVED) {
		tr->setPosition(Vector2D(m.ghost_data.x, m.ghost_data.y));
		tr->setRotation(m.ghost_data.rot);
	}
}

void GhostFighterSystem::update() {	
	// Movemos la nave
	tr->setVelocity(deAccelerate(tr->getVelocity()));

	// Aplicar cálculos
	tr->setPosition(tr->getPosition() + tr->getVelocity());
	
	// Mostrar la nave al otro lado si es necesario
	showAtOppositeSide(tr);
}