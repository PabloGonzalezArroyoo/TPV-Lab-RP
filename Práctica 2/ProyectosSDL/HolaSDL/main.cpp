// Pr�ctica 1: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"
#include "checkML.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// Check Memory Leaks (Nos informa de la basura no gestionada)
	try {
		Game* game = new Game("01");
		game->run();
		delete(game);
	}
	catch (string e) { cout << e << endl; }
	
	return 0;
}