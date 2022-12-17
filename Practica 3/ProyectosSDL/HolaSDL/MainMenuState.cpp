#include "MainMenuState.h"
#include "PlayState.h"

// Constructora
MainMenuState::MainMenuState(Game* g) : GameState(g) {
	// Imagen de inicio
	objects.push_back(new Image(game->getTexture(MainMenu)));

	// Botones correspondientes
	int centerWidth = WIN_WIDTH / 2 - BUTTON_WIDTH / 2;
	int centerHeight = WIN_HEIGHT / 2 - BUTTON_HEIGHT / 2;
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight - 70), game->getTexture(PlayButton), newGame, game));
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight + 50), game->getTexture(LoadButton), loadGame, game));
	objects.push_back(new MenuButton(Vector2D(centerWidth, centerHeight + 170), game->getTexture(ExitButton), quit, game));

}

// Llama al método de newGame de Game
void MainMenuState::newGame(Game* g) {
	g->getStateMachine()->changeState(new PlayState(g));
}

// Llama al método de loadGame de Game
void MainMenuState::loadGame(Game* g) {
	//Borramos consola
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif

	bool cargado = false;
	ifstream in;
	do {
		try {
			string playerId = " ";
			cout << "Introduzca el codigo numerico (0X) de la partida: ";
			cin >> playerId;
			in.open("saves/" + playerId + ".txt");
			if (!in.is_open()) throw FileNotFoundError("No existe una partida con ese codigo numerico");
			cargado = true;
		}
		catch (ArkanoidError e) {
			cout << endl << e.what() << endl;
			cout << "- Por favor, introduzca un nombre de archivo valido -" << endl;
			cargado = false;
		}
	} while (!cargado);

	g->getStateMachine()->changeState(new PlayState(g, in));
	in.close();
}

// Llama al método de quit de Game
void MainMenuState::quit(Game* g) {
	g->changeControl();
}