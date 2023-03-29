#include "Game.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "../sdlutils/SDLUtils.h"

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
	// Borrar Texturas
	for (int i = 0; i < NUM_TEXTURES; i++) delete(textures[i]);

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
		InputHandler::instance()->refresh();

		frameTime = SDL_GetTicks() - startTime;		// Actualizamos cuanto tiempo ha pasado desde el ultimo frame
		if (frameTime >= 5 && !exit) {				// Comprobamos si el tiempo de frame es mayor al ratio
			update();								// Actualizamos el estado del juego
			refresh();
			startTime = SDL_GetTicks();				// Actualizamos el valor de nuestra variable al valor de este frame
			render();
		}
	}

	if (exit) cout << "\nSaliste del juego... bye!" << endl;
}

// Renderizado
void Game::render() {
	//SDL_RenderClear(renderer);							// Limpiamos la pantalla

	gsm->currentState()->render();							// Renderizamos el estado actual

	//SDL_RenderPresent(renderer);							// Pintamos
}

// Actualizar entidades
void Game::update() {
	// UPDATE MÁQUINA DE ESTADOS
	gsm->currentState()->update();
}

void Game::refresh() {
	gsm->currentState()->refresh();
}

// Devuelve la textura correspondiente
Texture* Game::getTexture(int texture) {
	return textures[texture];
}