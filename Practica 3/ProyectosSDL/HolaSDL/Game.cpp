// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#include "Game.h"
#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"
#include "MainMenuState.h"

// Constructora
Game::Game() {
	// Inicialización de la ventana
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("ARKANOID V2", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw SDLError("Couldn't load screen.");

	// Variables de flujo
	exit = false;

	// Para cargar texturas
	for (int i = 0; i < NUM_TEXTURES; i++) {
		const TextureDescription& desc = textDescription[i];
		textures[i] = new Texture(renderer, "../images/" +  desc.filename + ".png", desc.hframes, desc.vframes);
	}
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
		handleEvents();

		frameTime = SDL_GetTicks() - startTime;		// Actualizamos cuanto tiempo ha pasado desde el ultimo frame
		if (frameTime >= FRAMERATE && !exit) {				// Comprobamos si el tiempo de frame es mayor al ratio
			update();								// Actualizamos el estado del juego
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

// Manejo del input
void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		gsm->currentState()->handleEvent(event);
	}
}

// Guardar en un archivo el estado del juego
void Game::saveGame() {
	// Pedir info de usuario
	string codUser = "";
	cout << "Introduce tu codigo de usuario (0X): ";
	cin >> codUser;
	gsm->popState();

	PlayState* play = static_cast<PlayState*> (gsm->currentState());
	ofstream out;
	out.open("saves/" + codUser + ".txt");
	play->saveToFile(out);
	out.close();
	gsm->pushState(new PauseState(this));
}

// Devuelve la textura correspondiente
Texture* Game::getTexture(int texture) {
	return textures[texture];
}