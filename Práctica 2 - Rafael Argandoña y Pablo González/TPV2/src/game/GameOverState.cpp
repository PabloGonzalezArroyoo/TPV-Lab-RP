#include "GameOverState.h"
#include "MainMenuState.h"
#include "Game.h"

// Constructora
GameOverState::GameOverState(Game* g) : GameState(g) {
	// Fondo rojo
	SDL_SetRenderDrawColor(sdlutils().renderer(), 123, 0, 36, 1);

	// A�adir el manager
	mng = new Manager();

	//// A�adir la nave (sin funcionalidad, solo imagen y posici�n)
	//Entity* ship = mng->addEntity();
	//ship->addComponent<Transform>(PLAYER_INITIAL_POS, Vector2D(), PLAYER_WIDTH, PLAYER_HEIGHT);
	//ship->addComponent<Image>(&sdlutils().images().at(FIGHTER));

	//// A�adir texto de gameOver
	//Entity* text = mng->addEntity();
	//auto txt = &sdlutils().msgs().at(GAME_OVER_MESSAGE);
	//text->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - txt->width() / 2, WIN_HEIGHT / 3 - txt->height() / 2),
	//	Vector2D(), txt->width(), txt->height());
	//text->addComponent<Image>(txt);

	//// A�adir texto de pausa
	//text = mng->addEntity();
	//txt = &sdlutils().msgs().at(PAUSE_MESSAGE);
	//text->addComponent<Transform>(Vector2D(WIN_WIDTH / 2 - txt->width() / 2, WIN_HEIGHT * 2 / 3 - txt->height() / 2),
	//	Vector2D(), txt->width(), txt->height());
	//text->addComponent<Image>(txt);
}

// Comprobamos si el jugador presiona SPACE para volver al menu principal
void GameOverState::update() {
	if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
		game->getStateMachine()->changeState(new MainMenuState(game));
	}
}