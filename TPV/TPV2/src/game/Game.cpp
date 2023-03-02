#include "Game.h"
#include "PlayState.h"
#include "MainMenuState.h"

// Constructora
Game::Game() {
	// Inicialización de la ventana
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	window = SDL_CreateWindow("ASTEROIDS", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 123, 123, 1);
	if (window == nullptr || renderer == nullptr) return ;

	//Cargamos fuentes
	string filename = "../image/fonts/NES-Chimera.ttf";
	myFont = new Font(filename, 20);

	// Variables de flujo
	exit = false;

	// Para cargar texturas de imagen
	for (int i = 0; i < NUM_TEXTURES - 3; i++) {
		const TextureDescription& desc = textDescription[i];
		textures[i] = new Texture(renderer, "../image/images/" + textDescription[i].filename + ".png");
	}

	// Creamos texturas de texto
	SDL_Color colour = { 0, 10, 87, 1 };
	string MM_MESSAGE = "PRESS SPACE TO START";
	string PAUSE_MESSAGE = "PRESS SPACE TO CONTINUE";
	string GAME_OVER = "GAME OVER";
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