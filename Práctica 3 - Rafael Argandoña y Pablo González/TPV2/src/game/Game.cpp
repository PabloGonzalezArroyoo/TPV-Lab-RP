#include "Game.h"
#include "MainMenuState.h"

// Constructora
Game::Game() {
	// Inicialización de la ventana
	SDLUtils::init("ASTEROIDS V1", WIN_WIDTH, WIN_HEIGHT, "resources/config/asteroids.resources.json");
	window = sdlutils().window();
	renderer = sdlutils().renderer();

	// Variables de flujo
	exit = false;

	// Máquina de estados
	gsm = new GameStateMachine(new MainMenuState(this));

	//Borramos consola
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

// Destructora
Game::~Game() {
	// Eliminar máquina de estados
	delete(gsm);

	sdlutils().~SDLUtils();
}

// Bucle principal del juego
void Game::run() {

	/*Dani
	uint32_t frameTime;
	startTime = SDL_GetTicks();
	
	

	// en el bucle
		frameTime = SDL_GetTicks() - startTime;

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

		if (frameTime >= DELAY_TIME)
	*/

	uint32_t startTime;
	startTime = SDL_GetTicks();
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	SDL_Delay(1500);

	// Bucle de juego
	while (!exit) {
		
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

		if (deltaTime * 10 >= 5) {				// Comprobamos si el tiempo de frame es mayor al ratio
			InputHandler::instance()->refresh();
			update();								// Actualizamos el estado del juego
			refresh();
			startTime = SDL_GetTicks();				// Actualizamos el valor de nuestra variable al valor de este frame
		}

		std::cout << deltaTime << " " << SDL_GetTicks() << " " << timeOffset << std::endl;

		if (ih().closeWindowEvent()) {
			exit = true;
		}
	}

	if (exit) cout << "\nSaliste del juego... bye!" << endl;
}

// Actualizar entidades
void Game::update() {
	SDL_RenderClear(renderer);							// Limpiamos la pantalla

	// UPDATE MÁQUINA DE ESTADOS
	gsm->currentState()->update();

	SDL_RenderPresent(renderer);							// Pintamos
}

void Game::refresh() {
	gsm->currentState()->refresh();
}