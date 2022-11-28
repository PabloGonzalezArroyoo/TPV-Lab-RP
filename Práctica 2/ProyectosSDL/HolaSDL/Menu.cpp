#include "Menu.h"

Menu::Menu() {
	// Inicialización de la ventana
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("MENU", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winW, winH, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw string("Error cargando SDL");

	// Inicializar tamaño, posición, textura y tipo
	w = winW; h = winH;
	pos = Vector2D();
	texture = new Texture(renderer, "../images/Menu.png", 1, 1);
	type = ' ';

	// Botones play y load
	play.x = 213; play.y = 254;
	play.w = 373; play.h = 100;
	load.x = 213; load.y = 373;
	load.w = 373; load.h = 100;
}

// Destructora
Menu::~Menu() {
	delete(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
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
	// Renderizado único
	render();						
	SDL_RenderPresent(renderer);

	// Bucle principal
	while (!exit) handleEvent();

	// Borrar render
	SDL_RenderClear(renderer);
}

// Procesar input 
void Menu::handleEvent() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Si se hace clic
		if (event.type == SDL_MOUSEBUTTONDOWN) type = setClick(event.button.x, event.button.y);
	}
}