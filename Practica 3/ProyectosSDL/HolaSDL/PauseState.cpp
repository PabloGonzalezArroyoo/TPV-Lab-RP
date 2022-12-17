#include "PauseState.h"
#include "MainMenuState.h"

// Constructora
PauseState::PauseState(Game* g) : GameState(g) {
	// Imagen de pausa
	objects.push_back(new Image(game->getTexture(Pause)));

	// Botones correspondientes
	int centerWidth = WIN_WIDTH / 2 - BUTTON_WIDTH / 2;
	int centerHeight = WIN_HEIGHT / 2 - BUTTON_HEIGHT / 2;
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight - 70), game->getTexture(ResumeButton), resume, game));
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight + 50), game->getTexture(SaveButton), saveGame, game));
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight + 170), game->getTexture(MainMenuButton), mainMenu, game));
}

// Llama al método de resume de Game
void PauseState::resume(Game* g) {
	g->getStateMachine()->popState();
}

// Llama al método de saveGame de Game
void PauseState::saveGame(Game* g) {
	//Borramos consola
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
	g->saveGame();
	cout << endl << "PARTIDA GUARDADA --- Si desea, puede seguir jugando" << endl;
}

// Llama al método de mainMenu de Game
void PauseState::mainMenu(Game* g) {
	g->getStateMachine()->discardStates();
	g->getStateMachine()->pushState(new MainMenuState(g));
}