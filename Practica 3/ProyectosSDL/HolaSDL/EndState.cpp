#include "EndState.h"

EndState::EndState() : GameState() {
	
}

EndState::EndState(Game* g, bool win) : GameState(g){
	//Imagen correspondiente
	if (win) objects.push_back(new Menu(game->getTexture(Winner)));
	else objects.push_back(new Menu(game->getTexture(GameOver)));

	objects.push_back(new MenuButton(Vector2D(400, 200), game->getTexture(RestartButton), newGame));
	objects.push_back(new MenuButton(Vector2D(400, 400), game->getTexture(ExitButton), mainMenu));
	objects.push_back(new MenuButton(Vector2D(400, 600), game->getTexture(MainMenuButton), quit));
}

void EndState::newGame(Game* g) {
	g->newGame();
}

void EndState::quit(Game* g) {
	g->quit();
}

void EndState::mainMenu(Game* g) {
	g->mainMenu();
}