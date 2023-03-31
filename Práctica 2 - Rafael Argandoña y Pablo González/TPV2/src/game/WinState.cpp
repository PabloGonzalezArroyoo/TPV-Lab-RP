#include "WinState.h"

WinState::WinState(Game* g) : GameState(g) {
	// Fondo amarillo
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 239, 255, 1);

	// Creamos el manager del estado
	mng = new Manager();

	// Sistemas
	mng->addSystem<GameCtrlSystem>();
	mng->addSystem<RenderSystem>();
	mng->addSystem<SoundSystem>();

	Message m;
	m.id = _m_INIT_STATE;
	m._state_data.st = WIN_STATE;
	m._state_data.g = g;
	mng->send(m);
}

void WinState::update() {
	// Si se presiona espacio, reproducir sonido y cargar estado
	if (InputHandler::instance()->isKeyJustDown(SDLK_SPACE)) {
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