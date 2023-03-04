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

	// Variables de flujo
	exit = false;

	// Cargamos fuentes
	myFont = new Font("resources/fonts/NES-Chimera.ttf", 20);

	// Para cargar texturas de imagen
	for (int i = 0; i < NUM_TEXTURES - 3; i++) {
		const TextureDescription& desc = textDescription[i];
		textures[i] = new Texture(renderer, "resources/images/" + textDescription[i].filename + ".png");
	}

	// Creamos texturas de textos
	string MM_MESSAGE = "PRESS SPACE TO START", PAUSE_MESSAGE = "PRESS SPACE TO CONTINUE", GAME_OVER = "GAME OVER";
	textures[NUM_TEXTURES - 3] = new Texture(renderer, MM_MESSAGE, (*myFont), { 0, 10, 87, 1 });
	textures[NUM_TEXTURES - 2] = new Texture(renderer, PAUSE_MESSAGE, (*myFont), { 255, 255, 255, 1 });
	textures[NUM_TEXTURES - 1] = new Texture(renderer, GAME_OVER, (*myFont), { 0, 10, 87, 1 });

	// Cargar sonidos
	for (int i = 0; i < NUM_SOUNDS; i++) {
		sounds[i] = new SoundEffect("resources/sound/" + soundsDescription[i] + ".wav");
	}

	// Cargar música
	for (int i = 0; i < NUM_MUSIC; i++) {
		music[i] = new Music("resources/music/" + musicDescription[i] + ".mp3");
	}

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
	for (int i = 0; i < NUM_SOUNDS; i++) delete(sounds[i]);
	for (int i = 0; i < NUM_MUSIC; i++) delete(music[i]);

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

// Devuelve la canción correspondiente
Music* Game::getMusic(int _music) {
	return music[_music];
}