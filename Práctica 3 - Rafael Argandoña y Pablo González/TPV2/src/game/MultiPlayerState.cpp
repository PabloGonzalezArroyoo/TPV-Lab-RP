#include "MultiPlayerState.h"

MultiPlayerState::MultiPlayerState() {
	mng = new Manager();

	mng->addSystem<NetworkSystem>();

	// Añadimos sistemas
	mng->addSystem<GameCtrlSystem>();
	mng->addSystem<FighterSystem>();
	mng->addSystem<BulletSystem>();
	mng->addSystem<CollisionsSystem>();
	mng->addSystem<RenderSystem>();
	mng->addSystem<SoundSystem>();
}