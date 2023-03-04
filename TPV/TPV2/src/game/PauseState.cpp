#include "PauseState.h"
#include "Game.h"

// Constructora
PauseState::PauseState(Game* g, int plLifes) : GameState(g) {
	// Añadir el manager
	mng = new Manager();

	// Añadir la nave como imagen y con vidas para el renderizado de las mismas
	Entity* ship = mng->addEntity();
	ship->addComponent<Transform>(PLAYER_INITIAL_POS, Vector2D(), PLAYER_WIDTH, PLAYER_HEIGHT);
	ship->addComponent<Image>(g->getTexture(FIGTHER));
	ship->addComponent<Health>(g->getTexture(HEALTH), plLifes);

	// Añadir texto de pause
	Entity* text = mng->addEntity();
	auto txt = g->getTexture(PAUSE_MESSAGE);
	text->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - txt->width() / 2, WIN_HEIGHT * 2 / 3 - txt->height() / 2),
		Vector2D(), txt->width(), txt->height());
	text->addComponent<Image>(txt);
}

// Manejo del input en el pasueState
void PauseState::update() {
	// Si el jugador presiona espacio, continuar
	if (InputHandler::instance()->isKeyJustDown(SDLK_SPACE)) {
		game->getSound(SELECT)->play();
		game->getStateMachine()->popState();
	}
	// Si el jugador presiona escape, salir
	else if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
		game->changeControl();
	}
}