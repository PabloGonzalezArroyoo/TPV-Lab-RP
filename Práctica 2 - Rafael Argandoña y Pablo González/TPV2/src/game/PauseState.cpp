#include "PauseState.h"
#include "../systems/RenderSystem.h"
#include "Game.h"

// Constructora
PauseState::PauseState(Game* g, int plLifes) : GameState(g) {
	// A�adir el manager
	mng = new Manager();

	// A�adir la nave (sin funcionalidad, solo imagen y posici�n)
	Entity* ship = mng->addEntity();
	mng->setHandler(_hdlr_FIGHTER, ship);
	mng->addComponent<Transform>(ship, PLAYER_INITIAL_POS, PLAYER_WIDTH, PLAYER_HEIGHT);
	mng->addComponent<Health>(ship, plLifes);

	// Sistemas
	mng->addSystem<RenderSystem>();

	Message m;
	m.id = _m_INIT_STATE;
	m._state_data.st = PAUSE_STATE;
	m._state_data.g = g;
	mng->send(m);
}

// Manejo del input en el pasueState
void PauseState::update() {
	GameState::update();

	// Si el jugador presiona espacio, continuar
	if (InputHandler::instance()->isKeyJustDown(SDLK_SPACE)) {
		sdlutils().soundEffects().at(SELECT).play();
		game->getStateMachine()->popState();
	}
	// Si el jugador presiona escape, salir
	else if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
		game->changeControl();
	}
}