#include "EndState.h"
#include "GameStateMachine.h"

EndState::EndState() : GameState() {
	
}

EndState::EndState(Game* g, bool win) : GameState(g){
	//Imagen correspondiente
	if (win) objects.push_back(new Menu(game->getTexture(Winner)));
	else objects.push_back(new Menu(game->getTexture(GameOver)));

	// Botones correspondientes
	int centerWidth = WIN_WIDTH / 2 - BUTTON_WIDTH / 2;
	int centerHeight = WIN_HEIGHT / 2 - BUTTON_HEIGHT / 2;
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight - 70), game->getTexture(RestartButton), newGame));
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight + 50), game->getTexture(MainMenuButton), mainMenu));
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight + 170), game->getTexture(ExitButton), quit));
}

void EndState::newGame(Game* g) {
	g->getGameStateMachine()->changeState(new PlayState(g));
}

void EndState::quit(Game* g) {
	g->changeControl();
	delete(g->getGameStateMachine());
}

void EndState::mainMenu(Game* g) {
	g->getGameStateMachine()->discardStates();
	g->getGameStateMachine()->pushState(new MainMenuState(g));
}