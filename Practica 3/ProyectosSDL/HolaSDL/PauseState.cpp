#include "PauseState.h"

PauseState::PauseState() : GameState() {
	
}

PauseState::PauseState(Game* g) : GameState(g) {
	objects.push_back(new MenuButton(Vector2D(400, 200), game->getTexture(ResumeButton), newGame));
	objects.push_back(new MenuButton(Vector2D(400, 400), game->getTexture(SaveButton), mainMenu));
	objects.push_back(new MenuButton(Vector2D(400, 600), game->getTexture(ExitButton), quit));
}

void PauseState::newGame(Game* g) {
	g->newGame();
}