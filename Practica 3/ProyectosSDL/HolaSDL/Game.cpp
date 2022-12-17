// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#include "Game.h"

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

	// Máquina de estados
	gsm = new GameStateMachine(new MainMenuState(this));
}

// Destructora
Game::~Game() {
	// Borrar Texturas
	for (int i = 0; i < NUM_TEXTURES; i++) delete(textures[i]);

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

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		gsm->currentState()->handleEvent(event);
	}
}

// Guardar en arhivo
/*
void Game::saveToFile(string filename) {

	ofstream out;
	out.open("saves/" + filename + ".txt");

	// Guardar nivel actual y vida
	out << currentLevel << " " << life << endl;

	// Guardar objetos de la lista de objetos
	for (list<ArkanoidObject*>::iterator it = objects.begin(); it != next(itBall); it++) {
		(*it)->saveToFile(out); out << endl;
	}

	// Guardar los rewards en caso de haber
	if (objects.size() > 5)
	{
		out << (objects.size() - 6) << endl;
		for (list<ArkanoidObject*>::iterator it = next(itBall); it != objects.end(); it++) {
			(*it)->saveToFile(out); out << endl;
		}
	}
	
	out.close();
}
*/

// Debe cargar un juego completamente nuevo, es decir, cargar PlayState
void Game::newGame() {
	gsm->changeState(new PlayState(this));
}

// Debe cargar un juego completamente nuevo, es decir, cargar PlayState, pero a partir de datos previos
void Game::loadGame() {
	bool cargado = false;
	ifstream in;
	do {
		try{
			string playerId = " ";
			cout << "Introduzca el codigo numerico (0X) de la partida: ";
			cin >> playerId;
			in.open("saves/" + playerId + ".txt");
			cargado = true;
		}
		catch (ArkanoidError e) {
			cout << e.what() << endl;
			cout << "- Por favor, introduzca un nombre de archivo válido -";
			cargado = false;
		}
	} while (!cargado);

	gsm->changeState(new PlayState(this, in));
	in.close();
}


void Game::saveGame() {
	// Pedir info de usuario
	string codUser = "";
	cout << "Introduce tu codigo de usuario (0X): ";
	cin >> codUser;
	resume();

	PlayState* play = static_cast<PlayState*> (gsm->currentState());
	ofstream out;
	out.open("saves/" + codUser + ".txt");
	play->saveToFile(out);
	out.close();
	pause();
}

// Debe cerrar el juego
void Game::quit() {
	exit = true;
	delete(gsm);
}

// Al llamarse en el PauseState, debe borrarse y dejar que el estado de debajo se ejecute
void Game::resume() {
	gsm->popState();
}

// Borrar todos los estados previos y empezar una nueva pila con el menú como único estado
void Game::mainMenu() {
	gsm->discardStates();
	gsm->pushState(new MainMenuState(this));
}

// Añade un nuevo estado de pausa a la pila
void Game::pause() {
	gsm->pushState(new PauseState(this));
}

void Game::end(bool win) {
	gsm->changeState(new EndState(this, win));
}

// Devuelve la textura correspondiente
Texture* Game::getTexture(int texture) {
	return textures[texture];
}