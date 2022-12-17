#include "PauseState.h"
#include "GameStateMachine.h"

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
	g->getGameStateMachine()->pushState(new PauseState(g));
}

// Llama al método de saveGame de Game
void PauseState::saveGame(Game* g) {
	// Pedir info de usuario
	string codUser = "";
	cout << "Introduce tu codigo de usuario (0X): ";
	cin >> codUser;
	//resume();

	PlayState* play = static_cast<PlayState*> (g->getGameStateMachine()->currentState());
	ofstream out;
	out.open("saves/" + codUser + ".txt");
	play->saveToFile(out);
	out.close();
	//pause();
}

// Llama al método de mainMenu de Game
void PauseState::mainMenu(Game* g) {
	g->getGameStateMachine()->discardStates();
	g->getGameStateMachine()->pushState(new MainMenuState(g));
}