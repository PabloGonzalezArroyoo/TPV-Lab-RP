#include "MultiPlayerState.h"

MultiPlayerState::MultiPlayerState(Game* g) : GameState(g) {
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
	m._state_data.g = g;
	mng->send(m);

	// Mensaje para reproducir música
	Message m2;
	m2.id = _m_PLAY_MUSIC;
	m2._music_data.music = &sdlutils().musics().at(MULTI_MUSIC);
	mng->send(m2);
}