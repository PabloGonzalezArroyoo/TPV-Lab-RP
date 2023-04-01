#include "PauseState.h"
#include "../systems/RenderSystem.h"
#include "Game.h"

// Constructora
PauseState::PauseState(Game* g, int plLifes) : GameState(g) {
	// Añadir el manager
	mng = new Manager();

	// Añadir la nave (sin funcionalidad, solo imagen y posición)
	Entity* ship = mng->addEntity();
	mng->setHandler(_hdlr_FIGHTER, ship);
	mng->addComponent<Transform>(ship, PLAYER_INITIAL_POS, PLAYER_WIDTH, PLAYER_HEIGHT);
	mng->addComponent<Health>(ship, plLifes);

	// Añadimos sistemas
	mng->addSystem<GameCtrlSystem>();
	mng->addSystem<RenderSystem>();
	mng->addSystem<SoundSystem>();

	// Mensaje de inicio de estado
	Message m;
	m.id = _m_INIT_STATE;
	m._state_data.st = PAUSE_STATE;
	m._state_data.g = g;
	m._state_data.l = plLifes;
	mng->send(m);
}

// Manejo del input en el pasueState
void PauseState::update() {
	GameState::update();

	// Si el jugador presiona espacio, continuar
	if (InputHandler::instance()->isKeyJustDown(SDLK_SPACE)) {
		Message m;
		m.id = _m_SPACEBAR_PRESSED;
		mng->send(m);
	}
	// Si el jugador presiona escape, salir
	else if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
		Message m;
		m.id = _m_ESC_PRESSED;
		mng->send(m);
	}
}