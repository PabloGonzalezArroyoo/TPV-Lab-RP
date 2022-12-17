#include "MainMenuState.h"
#include "GameStateMachine.h"

// Constructora
MainMenuState::MainMenuState(Game* g) : GameState(g) {
	// Imagen de inicio
	objects.push_back(new Menu(game->getTexture(MainMenu)));

	// Botones correspondientes
	int centerWidth = WIN_WIDTH / 2 - BUTTON_WIDTH / 2;
	int centerHeight = WIN_HEIGHT / 2 - BUTTON_HEIGHT / 2;
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight - 70), game->getTexture(PlayButton), newGame));
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight + 50), game->getTexture(LoadButton), loadGame));
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight + 170), game->getTexture(ExitButton), quit));
}

// Llama al m�todo de newGame de Game
void MainMenuState::newGame(Game* g) {
	g->getGameStateMachine()->changeState(new PlayState(g));
}

// Llama al m�todo de loadGame de Game
void MainMenuState::loadGame(Game* g) {
	bool cargado = false;
	ifstream in;
	do {
		try {
			string playerId = " ";
			cout << "Introduzca el codigo numerico (0X) de la partida: ";
			cin >> playerId;
			in.open("saves/" + playerId + ".txt");
			cargado = true;
		}
		catch (ArkanoidError e) {
			cout << e.what() << endl;
			cout << "- Por favor, introduzca un nombre de archivo v�lido -";
			cargado = false;
		}
	} while (!cargado);

	g->getGameStateMachine()->changeState(new PlayState(g, in));
	in.close();
}

// Llama al m�todo de quit de Game
void MainMenuState::quit(Game* g) {
	g->changeControl();
	delete(g->getGameStateMachine());
}