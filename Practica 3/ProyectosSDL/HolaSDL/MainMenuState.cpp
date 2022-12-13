#include "MainMenuState.h"

MainMenuState::MainMenuState() {
	game = nullptr;
}

MainMenuState::MainMenuState(Game* g) {
	game = g;

	//Creamos la imagen de menu y los botones correspondientes
	objects.push_back(new Menu(game->getTexture(MainMenu)));
	objects.push_back(new MenuButton(Vector2D(200, 100), game->getTexture(PlayButton), newGame));
	objects.push_back(new MenuButton(Vector2D(200, 200), game->getTexture(LoadButton), loadGame));
	objects.push_back(new MenuButton(Vector2D(200, 300), game->getTexture(ExitButton), quit));
}

void MainMenuState::newGame(Game* g) {
	g->newGame();
}

void MainMenuState::loadGame(Game* g) {
	g->loadGame();
}

void MainMenuState::quit(Game* g) {
	g->quit();
}