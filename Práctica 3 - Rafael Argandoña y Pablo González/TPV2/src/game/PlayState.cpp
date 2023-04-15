#include "PlayState.h"

// Constructora
PlayState::PlayState(Game* g) : GameState(g) {
	// Fondo azul
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 123, 123, 1);

	// Creamos el manager del estado
	mng = new Manager();

	// Añadimos sistemas
	mng->addSystem<GameCtrlSystem>();
	mng->addSystem<FighterSystem>();
	mng->addSystem<AsteroidsSystem>();
	mng->addSystem<BulletSystem>();
	mng->addSystem<CollisionsSystem>();
	mng->addSystem<RenderSystem>();
	mng->addSystem<SoundSystem>();

	// Mensaje de inicio de estado
	Message m1;
	m1.id = _m_INIT_STATE;
	m1._state_data.st = PLAY_STATE;
	m1._state_data.g = g;
	mng->send(m1);

	// Mensaje para reproducir música
	Message m2;
	m2.id = _m_PLAY_MUSIC;
	m2._music_data.music = &sdlutils().musics().at(GALAXY);
	mng->send(m2);
}

void PlayState::update() {
	GameState::update();

	// Si se pulsa escape, lanzar estado de pausa
	if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
		Message m;
		m.id = _m_ESC_PRESSED;
		mng->send(m);
	}
}