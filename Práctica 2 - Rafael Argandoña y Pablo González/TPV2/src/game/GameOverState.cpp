#include "GameOverState.h"
#include "Game.h"

// Constructora
GameOverState::GameOverState(Game* g) : GameState(g) {
	// Fondo rojo
	SDL_SetRenderDrawColor(sdlutils().renderer(), 123, 0, 36, 1);

	// Añadir el manager
	mng = new Manager();

	mng->addSystem<GameCtrlSystem>();
	mng->addSystem<RenderSystem>();
	mng->addSystem<SoundSystem>();
	
	Message m1;
	m1.id = _m_INIT_STATE;
	m1._state_data.st = GAMEOVER_STATE;
	m1._state_data.g = g;
	mng->send(m1);

	Message m2;
	m2.id = _m_PLAY_MUSIC;
	m2._music_data.music = &sdlutils().musics().at(GAMEOVER);
	mng->send(m2);
}

// Comprobamos si el jugador presiona SPACE para volver al menu principal
void GameOverState::update() {
	GameState::update();
	if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
		Message m;
		m.id = _m_SPACEBAR_PRESSED;
		mng->send(m);
	}
	// Si se pulsa escape, cerrar ventana
	else if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
		Message m;
		m.id = _m_ESC_PRESSED;
		mng->send(m);
	}
}