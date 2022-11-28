// Pr�ctica 1: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"
#include "Menu.h"
#include "checkML.h"
#include <iostream>

using namespace std;

// Carga un juego a partir de una partida guardada
void loadGame() {
	// Pedir usuario
	string playerId = " ";
	cout << "Introduzca el codigo de la partida: ";
	cin >> playerId;

	Game* game = new Game(playerId);	// Cargar juego a partir de archivo
	game->run();						// Bucle
	delete(game);						// Borrar memoria
}

// Carga un juego vac�o (nuevo)
void newGame() {
	Game* game = new Game();			// Cargar juego
	game->run();						// Bucle
	delete(game);						// Borrar memoria
}

int main(int argc, char* argv[]){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// Check Memory Leaks (Nos informa de la basura no gestionada)
	
	// Men� 
	Menu* menu = new Menu();
	menu->run();
	char type = menu->getType();
	delete(menu);

	// Juego
	try {
		if (type == 'L') loadGame();
		else if (type == 'N') newGame();
	}
	catch (string e) { cout << e << endl; }
	
	return 0;
}