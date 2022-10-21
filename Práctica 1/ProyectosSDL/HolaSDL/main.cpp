// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido

#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"
#include "checkML.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
	Game* game = nullptr;
	Game g = Game();
	game = &g;
	game->render();

	return 0;
}