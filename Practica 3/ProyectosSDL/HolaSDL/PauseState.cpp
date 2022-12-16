#include "PauseState.h"

// Constructora
PauseState::PauseState(Game* g) : GameState(g) {
	// Imagen de pausa
	objects.push_back(new Menu(game->getTexture(Pause)));

	// Botones correspondientes
	int centerWidth = WIN_WIDTH / 2 - BUTTON_WIDTH / 2;
	int centerHeight = WIN_HEIGHT / 2 - BUTTON_HEIGHT / 2;
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight - 70), game->getTexture(ResumeButton), resume));
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight + 50), game->getTexture(SaveButton), saveGame));
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight + 170), game->getTexture(MainMenuButton), mainMenu));
}

// Llama al método de resume de Game
void PauseState::resume(Game* g) {
	g->resume();
}

// Llama al método de saveGame de Game
void PauseState::saveGame(Game* g) {
	g->saveGame();
}

// Llama al método de mainMenu de Game
void PauseState::mainMenu(Game* g) {
	g->mainMenu();
}