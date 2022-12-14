#include "MainMenuState.h"

MainMenuState::MainMenuState() : GameState() {
}

MainMenuState::MainMenuState(Game* g) : GameState(g) {

	//Creamos la imagen de menu y los botones correspondientes
	objects.push_back(new Menu(game->getTexture(MainMenu)));
	objects.push_back(new MenuButton(Vector2D(300, 200), game->getTexture(PlayButton), newGame));
	objects.push_back(new MenuButton(Vector2D(300, 300), game->getTexture(LoadButton), loadGame));
	objects.push_back(new MenuButton(Vector2D(300, 400), game->getTexture(ExitButton), quit));
}

void MainMenuState::handleEvent(SDL_Event e) {
	bool control = false;
	for (list<GameObject*>::iterator it = next(objects.begin()); it != objects.end() && !control; it++) {
		MenuButton* myB = dynamic_cast<MenuButton*> (*it);
		myB->handleEvent(e);
		if (myB->getState() == 2) { control = true; myB->myC(game); }
	}
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