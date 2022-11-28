#include "Menu.h"

Menu::Menu(Texture* _texture) {
	// Inicialización de la ventana
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw string("Error cargando SDL");

	w = winWidth; h = winHeight;
	pos = Vector2D();
	texture = _texture;
	type = ' ';

	
}

char Menu::setClick(double x, double y) {
	cout << x << " " << y;
	if ((x <= play.x && x < play.x + play.w) && (y <= play.y && y < play.y + play.h)) {
		exit = true;
		return 'N';
	}
	else if ((x <= load.x && x < load.x + load.w) && (y <= load.y && y < load.y + load.h)) {
		exit = true;
		return 'L';
	}
	else return ' ';
}

void Menu::run() {
	render();
	SDL_Event event;
	char type = ' ';
	while (!exit) {
		handleEvent(event.button);
	}
}

void Menu::handleEvent(SDL_MouseButtonEvent event) {
	type = setClick(event.x, event.y);
}