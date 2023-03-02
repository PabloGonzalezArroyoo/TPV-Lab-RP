#include "PauseState.h"
#include "Game.h"

PauseState::PauseState(Game* g, int plLifes) : GameState(g) {
	mng = new Manager();
	Entity* ship = mng->addEntity();
	ship->addComponent<Transform>(PLAYER_INITIAL_POS, Vector2D(), PLAYER_WIDTH, PLAYER_HEIGHT);
	ship->addComponent<Image>(g->getTexture(FIGTHER));
	ship->addComponent<Health>(g->getTexture(HEALTH), plLifes);
	//Añadir texto PRESS SPACE TO CONTINUE

	Entity* text = mng->addEntity();
	auto txt = g->getTexture(PAUSE_MESSAGE);
	text->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - txt->width() / 2, WIN_HEIGHT * 2 / 3 - txt->height() / 2),
		Vector2D(), txt->width(), txt->height());
	text->addComponent<Image>(txt);
}

void PauseState::update() {
	if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
		game->getStateMachine()->popState();
	}
}