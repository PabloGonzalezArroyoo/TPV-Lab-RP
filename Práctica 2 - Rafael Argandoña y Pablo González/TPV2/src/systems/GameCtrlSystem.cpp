#include "GameCtrlSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"
#include "../game/PauseState.h"

void GameCtrlSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_INIT_STATE: 
			state = m._state_data.st;
			game = m._state_data.g;
			break;
		
		case _m_PLAYER_DAMAGED:
			onCollision_FighterAsteroid();
			break;
	}
}

void GameCtrlSystem::initSystem() {

}

void GameCtrlSystem::update() {

}

void GameCtrlSystem::onAsteroidsExtinction() {

}

void GameCtrlSystem::onCollision_FighterAsteroid() {
	Health* h = mngr->getComponent<Health>(mngr->getHandler(_hdlr_FIGHTER));
	h->setLives(h->getLifes() - 1);

	if (h->getLifes() > 0) {
		// LANZAR EL MENSAJE DE QUE ACABO LA RONDA
		Message m;
		m.id = _m_ROUND_OVER;
		mngr->send(m);

		// LANZAS LA PAUSA
		game->getStateMachine()->pushState(new PauseState(game, h->getLifes()));
	}

	else {
		// LANZAR estado de derrota
	}

}