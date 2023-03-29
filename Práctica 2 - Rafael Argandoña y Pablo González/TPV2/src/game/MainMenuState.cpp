#include "MainMenuState.h"
#include "PlayState.h"
#include "../systems/RenderSystem.h"
#include "Game.h"

// Constructora
MainMenuState::MainMenuState(Game* g) : GameState(g) {
	// Fondo verde
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 123, 17, 1);

	// Creamos el manager del estado
	mng = new Manager();

	// Añadir la nave (sin funcionalidad, solo imagen y posición)
	Entity* ship = mng->addEntity();
	mng->setHandler(_hdlr_FIGHTER, ship);
	mng->addComponent<Transform>(ship, PLAYER_INITIAL_POS, PLAYER_WIDTH, PLAYER_HEIGHT);

	// Sistemas
	mng->addSystem<RenderSystem>();

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
		sdlutils().soundEffects().at(SELECT).play();
  		game->getStateMachine()->changeState(new PlayState(game));
	}
	// Si se pulsa escape, cerrar ventana
	else if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
		game->changeControl();
	}
}