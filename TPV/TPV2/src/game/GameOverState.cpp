#include "GameOverState.h"
#include "MainMenuState.h"
#include "Game.h"

GameOverState::GameOverState(Game* g) : GameState(g) {
	mng = new Manager();
	Entity* ship = mng->addEntity();
	ship->addComponent<Transform>(PLAYER_INITIAL_POS, Vector2D(), PLAYER_WIDTH, PLAYER_HEIGHT);
	ship->addComponent<Image>(g->getTexture(FIGTHER));

	//AÑADIR LOS DOS TEXTOS: GAMEOVER Y PRESIONA SPACE TO CONTINUE
	Entity* text = mng->addEntity();
	auto txt = g->getTexture(GO_MESSAGE);
	text->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - txt->width() / 2, WIN_HEIGHT / 3 - txt->height() / 2),
		Vector2D(), txt->width(), txt->height());
	text->addComponent<Image>(txt);


	text = mng->addEntity();
	txt = g->getTexture(PAUSE_MESSAGE);
	text->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - txt->width() / 2, WIN_HEIGHT * 2 / 3 - txt->height() / 2),
		Vector2D(), txt->width(), txt->height());
	text->addComponent<Image>(txt);
}

void GameOverState::update() {
	if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
		game->getStateMachine()->changeState(new MainMenuState(game));
	}
}