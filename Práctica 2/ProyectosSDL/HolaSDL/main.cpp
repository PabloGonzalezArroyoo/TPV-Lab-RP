// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"
#include "Menu.h"
#include "checkML.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// Check Memory Leaks (Nos informa de la basura no gestionada)
	Menu* menu = new Menu();
	menu->run();
	char type = menu->getType();
	delete(menu);

	try {
		if (type == 'L') {
			string playerId = " ";
			cout << "Introduzca el codigo de la partida: ";
			cin >> playerId;
			Game* game = new Game(playerId);
			game->run();
			delete(game);
		}
		else if (type == 'N') {
			Game* game = new Game();
			game->run();
			delete(game);
		}
	}
	catch (string e) { cout << e << endl; }
	
	return 0;
}