#include "Menu.h"

Menu::Menu(Vector2D _pos, uint _w, uint _h, Texture* _texture) : ArkanoidObject(_pos, _w, _h, _texture) {

	type = ' ';

	// Botones play y load
	play.x = 213; play.y = 254;
	play.w = 373; play.h = 100;
	load.x = 213; load.y = 373;
	load.w = 373; load.h = 100;
}

// Destructora
Menu::~Menu() {
	
}

// Devuelve el carcater correspondiente a si se selecciona una nueva partida ('N'), cargar partida ('L') o ninguno (' ')
char Menu::setClick(double x, double y) {
	if ((x >= play.x && x < play.x + play.w) && (y >= play.y && y < play.y + play.h)) {		// Si pulsa dentro del rectángulo de play
		exit = true;
		return 'N';
	}
	else if ((x >= load.x && x < load.x + load.w) && (y >= load.y && y < load.y + load.h)) { // Si pulsa dentro del rectángulo de load
		exit = true;
		return 'L';
	}
	else return ' ';																		// Si no lo hace en ninguno
}

// Bucle principal
void Menu::run() {
	// Bucle principal
	while (!exit) handleEvent();
}

// Procesar input 
void Menu::handleEvent() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Si se hace clic
		if (event.type == SDL_MOUSEBUTTONDOWN) type = setClick(event.button.x, event.button.y);
	}
}