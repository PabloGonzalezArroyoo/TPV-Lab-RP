#include "MainMenuState.h"

MainMenuState::MainMenuState(Game* g) {
	GameState(g);

	//Creamos la imagen de menu y los botones correspondientes
	objects.push_back(new MenuButton(Vector2D(200, 100), game->getTexture(PlayButton), newGame));
	objects.push_back(new MenuButton(Vector2D(200, 200), game->getTexture(LoadButton), loadGame));
	objects.push_back(new MenuButton(Vector2D(200, 300), game->getTexture(ExitButton), quit));
}