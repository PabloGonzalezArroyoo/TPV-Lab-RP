#include "EndState.h"
#include "MainMenuState.h"
#include "PlayState.h"

EndState::EndState() : GameState() {
	
}

EndState::EndState(Game* g, bool win) : GameState(g){
	//Imagen correspondiente
	if (win) objects.push_back(new Menu(game->getTexture(Winner)));
	else objects.push_back(new Menu(game->getTexture(GameOver)));

	// Botones correspondientes
	int centerWidth = WIN_WIDTH / 2 - BUTTON_WIDTH / 2;
	int centerHeight = WIN_HEIGHT / 2 - BUTTON_HEIGHT / 2;
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight - 70), game->getTexture(RestartButton), newGame, game));
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight + 50), game->getTexture(MainMenuButton), mainMenu, game));
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight + 170), game->getTexture(ExitButton), quit, game));
}

void EndState::newGame(Game* g) {
	g->getStateMachine()->changeState(new PlayState(g));
}

void EndState::quit(Game* g) {
	g->changeControl();
}

void EndState::mainMenu(Game* g) {
	g->getStateMachine()->changeState(new MainMenuState(g));
}