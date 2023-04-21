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
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	SDL_Delay(1500);
	while (!exit) {
		frameTime = SDL_GetTicks() - startTime;		// Actualizamos cuanto tiempo ha pasado desde el ultimo frame
		if (frameTime >= 5 && !exit) {				// Comprobamos si el tiempo de frame es mayor al ratio
			InputHandler::instance()->refresh();
			update();								// Actualizamos el estado del juego
			refresh();
			startTime = SDL_GetTicks();				// Actualizamos el valor de nuestra variable al valor de este frame
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