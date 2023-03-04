#include "MainMenuState.h"
#include "PlayState.h"
#include "Game.h"

// Constructora
MainMenuState::MainMenuState(Game* g) : GameState(g) {
	// Fondo verde
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 123, 17, 1);

	// Creamos el manager del estado
	mng = new Manager();

	// Añadir la nave (sin funcionalidad, solo imagen y posición)
	Entity* ship = mng->addEntity();
	ship->addComponent<Transform>(Vector2D(WIN_WIDTH/2 - PLAYER_WIDTH/2, WIN_HEIGHT/2 - PLAYER_HEIGHT/2),
		Vector2D(), PLAYER_WIDTH, PLAYER_HEIGHT);
	ship->addComponent<Image>(g->getTexture(FIGTHER));

	// Añadir texto de mainMenu
	Entity* text = mng->addEntity();
	auto txt = g->getTexture(MM_MESSAGE);
	text->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - txt->width() / 2, WIN_HEIGHT * 2 / 3 - txt->height()/2),
		Vector2D(), txt->width(), txt->height());
	text->addComponent<Image>(txt);
}

// Manejo del input en el mainMenu
void MainMenuState::update() {
	// Si se presiona espacio, reproducir sonido y cargar estado
	if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
		game->getSound(SELECT)->play();
		game->getStateMachine()->changeState(new PlayState(game));
	}
	// Si se pulsa escape, cerrar ventana
	else if (InputHandler::instance()->isKeyDown(SDLK_ESCAPE)) {
		game->changeControl();
	}
}