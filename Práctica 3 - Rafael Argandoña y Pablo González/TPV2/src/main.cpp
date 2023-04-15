// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include "utils/chekML.h"
#include "game/Game.h"

int main(int ac, char **av) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// Check Memory Leaks (Nos informa de la basura no gestionada)

	try {
		Game* g = new Game();
		g->run();
		delete g;
	}
	catch (string e){
		cout << e << endl;
	}

	return 0;
}