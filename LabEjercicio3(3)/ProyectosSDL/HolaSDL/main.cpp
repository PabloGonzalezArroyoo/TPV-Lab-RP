
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Game.h"

using namespace std;

using uint = unsigned int;

int main(int argc, char* argv[]){
	
	Game* game = nullptr;
	Game g = Game();
	game = &g;
	game->run();

	return 0;
}