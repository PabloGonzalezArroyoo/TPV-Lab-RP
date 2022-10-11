#include "Game.h"

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING); // Inicilaizamos SDL
	window = SDL_CreateWindow("Mierdón", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer = nullptr) throw string("No funca");
	
	string filename;
	// Creamos las texturas
	for (int i = 0; i < numTexture; i++) {
		if (i == 0) filename = "../images/background1.png";
		else if (i == 1) filename = "../images/dog.png";
		else filename = "../images/helicopter.png";

		Texture* txt = new Texture(renderer, filename);
		textures[i] = txt;
	}

	// Creamos los objetos
	dog = new Dog(textures[1]);
	helicopter = new Helicopter(textures[2]);
}

Game::~Game() {
	for (int i = 0; i < numTexture; i++) delete textures[i];
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run() {
	while (!exit) {
		handleEvents();
		update();
		render();
	}
}

void Game::update() {
	dog->move(winWidth, winHeight);
	helicopter->move(winWidth, winHeight);
}

void Game::render() const {
	SDL_RenderClear(renderer);
	SDL_Rect rect;
	rect.w = winWidth, rect.h = winHeight;
	textures[0]->render(rect);
	dog->render();
	helicopter->render();
	SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;
		dog->handleEvents(event);
		helicopter->handleEvents(event);
	}
}