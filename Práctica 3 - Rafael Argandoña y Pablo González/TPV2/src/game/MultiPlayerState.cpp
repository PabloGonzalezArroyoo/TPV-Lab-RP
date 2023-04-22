#include "MultiPlayerState.h"

MultiPlayerState::MultiPlayerState() {
	mng = new Manager();

	mng->addSystem<NetworkSystem>();

	// Añadimos sistemas
	mng->addSystem<GameCtrlSystem>();
	mng->addSystem<FighterSystem>();
	mng->addSystem<GhostFighterSystem>();
	mng->addSystem<BulletSystem>();
	mng->addSystem<CollisionsSystem>();
	mng->addSystem<RenderSystem>();
	mng->addSystem<SoundSystem>();

	// Mensaje de inicio de estado
	Message m;
	m.id = _m_INIT_STATE;
	m._state_data.st = MULTI_PLAYER;
	mng->send(m);
}