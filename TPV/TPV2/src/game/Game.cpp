#include "Game.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "../sdlutils/SDLUtils.h"

// Constructora
Game::Game() {
	// Inicialización de la ventana
	SDLUtils::init("ASTEROIDS V1", WIN_WIDTH, WIN_HEIGHT);
	window = sdlutils().window();
	renderer = sdlutils().renderer();
	SDL_SetRenderDrawColor(renderer, 0, 123, 123, 1);

	// Variables de flujo
	exit = false;

	// Para cargar texturas de imagen
	for (int i = 0; i < NUM_TEXTURES - 3; i++) {
		const TextureDescription& desc = textDescription[i];
		textures[i] = new Texture(renderer, "resources/images/" + textDescription[i].filename + ".png");
	}

	// Cargar sonidos
	for (int i = 0; i < NUM_SOUNDS; i++) {
		sounds[i] = new SoundEffect("resources/sound/" + soundsDescription[i] + ".wav");
	}

	// Cargamos fuentes
	myFont = new Font("resources/fonts/NES-Chimera.ttf", 20);

	// Creamos texturas de texto
	SDL_Color colour = { 0, 10, 87, 1 };
	string MM_MESSAGE = "PRESS SPACE TO START", PAUSE_MESSAGE = "PRESS SPACE TO CONTINUE", GAME_OVER = "GAME OVER";
	textures[NUM_TEXTURES - 3] = new Texture(renderer, MM_MESSAGE, (*myFont), colour);
	textures[NUM_TEXTURES - 2] = new Texture(renderer, PAUSE_MESSAGE, (*myFont), {0,0,0,1}, {255, 255, 255, 1});
	textures[NUM_TEXTURES - 1] = new Texture(renderer, GAME_OVER, (*myFont), colour);

	//Borramos consola
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif

	// Máquina de estados
	gsm = new GameStateMachine(new MainMenuState(this));
}

// Destructora
Game::~Game() {
	// Borrar Texturas
	for (int i = 0; i < NUM_TEXTURES; i++) delete(textures[i]);
	for (int i = 0; i < NUM_SOUNDS; i++) delete(sounds[i]);

	// Eliminar máquina de estados
	delete(gsm);

	// Borrar render y window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
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
	SDL_RenderClear(renderer);								// Limpiamos la pantalla

	gsm->currentState()->render();							// Renderizamos el estado actual

	SDL_RenderPresent(renderer);							// Pintamos
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

// Devuelve el sonido correspondiente
SoundEffect* Game::getSound(int sound) {
	return sounds[sound];
}