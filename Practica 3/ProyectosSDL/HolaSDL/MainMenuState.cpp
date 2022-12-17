#include "MainMenuState.h"

// Constructora
MainMenuState::MainMenuState(Game* g) : GameState(g) {
	// Imagen de inicio
	objects.push_back(new Menu(game->getTexture(MainMenu)));

	// Botones correspondientes
	int centerWidth = WIN_WIDTH / 2 - BUTTON_WIDTH / 2;
	int centerHeight = WIN_HEIGHT / 2 - BUTTON_HEIGHT / 2;
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight - 70), game->getTexture(PlayButton), newGame));
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight + 50), game->getTexture(LoadButton), loadGame));
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight + 170), game->getTexture(ExitButton), quit));
}

// Llama al método de newGame de Game
void MainMenuState::newGame(Game* g) {
	g->newGame();
}

// Llama al método de loadGame de Game
void MainMenuState::loadGame(Game* g) {
	g->loadGame();
}

// Llama al método de quit de Game
void MainMenuState::quit(Game* g) {
	g->quit();
}