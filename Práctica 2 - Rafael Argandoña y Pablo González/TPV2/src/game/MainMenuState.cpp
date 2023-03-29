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
	mng->addComponent<Transform>(ship, Vector2D(WIN_WIDTH/2 - PLAYER_WIDTH/2, WIN_HEIGHT/2 - PLAYER_HEIGHT/2), PLAYER_WIDTH, PLAYER_HEIGHT);

	// Sistemas
	mng->addSystem<RenderSystem>();
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