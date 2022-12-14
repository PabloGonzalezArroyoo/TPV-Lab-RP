// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#include "Game.h"
#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"
#include "MainMenuState.h"

// Constructora
Game::Game() {
	// Inicializaci�n de la ventana
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

	// M�quina de estados
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
		if (frameTime >= FRAMERATE) {				// Comprobamos si el tiempo de frame es mayor al ratio
			update();								// Actualizamos el estado del juego
			startTime = SDL_GetTicks();				// Actualizamos el valor de nuestra variable al valor de este frame
		}

		render();
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
	// UPDATE M�QUINA DE ESTADOS
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

// Pregunta por el c�digo de usuario y llama al m�todo de guardar en archivo
void Game::userSaving() {
	// Quitar la ventana de SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	// Marcar que se ha salido
	exit = true;

	// Pedir info de usuario
	string codUser = "";
	cout << "Introduce tu codigo de usuario (0X): ";
	cin >> codUser;
	saveToFile(codUser);

	// Cerrar
	SDL_Quit();
}

// Cargar de archivo
void Game::loadFromFile(string filename) {
	ifstream in;
	in.open("saves/" + filename + ".txt");
	if (!in.is_open()) throw FileNotFoundError("Couldn't load file (" + filename + ".txt)"); // Si no se ha encontrado el archivo

	// Borrar lista anterior (objetos predeterminados)
	for (ArkanoidObject* myOb : objects) delete(myOb);
	objects.clear();

	// Leer nivel actual y vida
	in >> currentLevel;
	in >> life;

	// Punteros auxiliares
	BlocksMap* bmAux; Wall* wallAux; Paddle* pAux; Ball* bAux; Reward* rAux;

	// Leer blocksmap
	bmAux = new BlocksMap(WIN_WIDTH - 2 * WALL_WIDTH, WIN_HEIGTH / 2 - WALL_WIDTH, textures[Blocks], in);
	objects.push_back(bmAux);

	// Leer las paredes
	wallAux = new Wall(); wallAux->loadFromFile(in, textures[SideWall]); objects.push_back(wallAux);
	wallAux = new Wall(); wallAux->loadFromFile(in, textures[SideWall]); objects.push_back(wallAux);
	wallAux = new Wall(); wallAux->loadFromFile(in, textures[TopWall]); objects.push_back(wallAux);

	// Leer la pala
	pAux = new Paddle(); pAux->loadFromFile(in, textures[PaddleTxt]); objects.push_back(pAux);

	// Leer la bola y setear su iterador
	bAux = new Ball(); bAux->loadFromFile(in, textures[BallTxt]);
	bAux->setGameDepend(this); objects.push_back(bAux);
	itBall = prev(objects.end());
	
	// Comprobar si hay rewards y leerlas en caso afirmativo
	int numRewards = 0;
	in >> numRewards;
	for (int i = 0; i < numRewards; ++i) {
		rAux = new Reward(); rAux->loadFromFile(in, textures[Rewards]);
		rAux->setGameDepend(this); objects.push_back(rAux);
	}

	in.close();
}
*/

// Debe cargar un juego completamente nuevo, es decir, cargar PlayState
void Game::newGame() {
	gsm->changeState(new PlayState(this));
}

// Debe cargar un juego completamente nuevo, es decir, cargar PlayState, pero a partir de datos previos
void Game::loadGame() {
	gsm->changeState(new PlayState(this));
	//HACER CONSTRUCTORA Q RECIBA FLUJO
}

void Game::saveGame() {
	gsm->popState();
	//gsm->currentState()->saveToFile();
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

// Borrar todos los estados previos y empezar una nueva pila con el men� como �nico estado
void Game::mainMenu() {
	gsm->discardStates();
	gsm->pushState(new MainMenuState(this));
}

// A�ade un nuevo estado de pausa a la pila
void Game::pause() {
	gsm->pushState(new PauseState(this));
}

// Devuelve la textura correspondiente
Texture* Game::getTexture(int texture) {
	return textures[texture];
}