#include "MainMenuState.h"
#include "PlayState.h"
#include "Game.h"

MainMenuState::MainMenuState(Game* g) : GameState(g) {
	mng = new Manager();

	Entity* ship = mng->addEntity();
	ship->addComponent<Transform>(Vector2D(WIN_WIDTH/2 - PLAYER_WIDTH/2, WIN_HEIGHT/2 - PLAYER_HEIGHT/2),
		Vector2D(), PLAYER_WIDTH, PLAYER_HEIGHT);
	ship->addComponent<Image>(g->getTexture(FIGTHER));

	//AÑADIR TEXTO JAJA
	Entity* text = mng->addEntity();
	auto txt = g->getTexture(MM_MESSAGE);
	text->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - txt->width() / 2, WIN_HEIGHT * 2 / 3 - txt->height()/2),
		Vector2D(), txt->width(), txt->height());
	text->addComponent<Image>(txt);
}

void MainMenuState::update() {
	if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
		game->getSound(SELECT)->play();
		game->getStateMachine()->changeState(new PlayState(game));
	}
	else if (InputHandler::instance()->isKeyDown(SDLK_ESCAPE)) {
		game->changeControl();
	}
}