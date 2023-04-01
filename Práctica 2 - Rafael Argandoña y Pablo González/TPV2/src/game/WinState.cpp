#include "WinState.h"

WinState::WinState(Game* g) : GameState(g) {
	// Fondo amarillo
	SDL_SetRenderDrawColor(sdlutils().renderer(), 239, 255, 20, 1);

	// Creamos el manager del estado
	mng = new Manager();

	// Añadimos sistemas
	mng->addSystem<GameCtrlSystem>();
	mng->addSystem<RenderSystem>();
	mng->addSystem<SoundSystem>();

	// Mensaje de inicio de estado
	Message m1;
	m1.id = _m_INIT_STATE;
	m1._state_data.st = WIN_STATE;
	m1._state_data.g = g;
	mng->send(m1);

	// Mensaje para reproducir música
	Message m2;
	m2.id = _m_PLAY_MUSIC;
	m2._music_data.music = &sdlutils().musics().at(VICTORY);
	m2._music_data.loop = 0;
	mng->send(m2);
}

void WinState::update() {
	GameState::update();

	// Si se presiona espacio, reproducir sonido y cargar estado
	if (InputHandler::instance()->isKeyJustDown(SDLK_SPACE)) {
		Message m1;
		m1.id = _m_STOP_MUSIC;
		m1._music_data.music = &sdlutils().musics().at(VICTORY);
		mng->send(m1);

		Message m2;
		m2.id = _m_SPACEBAR_PRESSED;
		mng->send(m2);
	}
	// Si se pulsa escape, cerrar ventana
	else if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {

		Message m;
		m.id = _m_ESC_PRESSED;
		mng->send(m);
	}
}