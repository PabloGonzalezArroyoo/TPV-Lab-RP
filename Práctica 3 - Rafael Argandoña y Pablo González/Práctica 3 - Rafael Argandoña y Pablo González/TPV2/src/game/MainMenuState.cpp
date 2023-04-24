#include "MainMenuState.h"
#include "Game.h"

// Constructora
MainMenuState::MainMenuState(Game* g) : GameState(g) {
	// Fondo verde
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 123, 17, 1);

	// Creamos el manager del estado
	mng = new Manager();

	// Añadimos sistemas
	mng->addSystem<GameCtrlSystem>();
	mng->addSystem<RenderSystem>();
	mng->addSystem<SoundSystem>();

	// Mensaje de inicio de estado
	Message m;
	m.id = _m_INIT_STATE;
	m._state_data.st = MAINMENU_STATE;
	m._state_data.g = g;
	mng->send(m);
}

// Manejo del input en el mainMenu
void MainMenuState::update() {
	GameState::update();

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

	else if (InputHandler::instance()->isKeyJustDown(SDLK_m)) {
		Message m;
		m.id = _m_M_PRESSED;
		mng->send(m);
	}
}