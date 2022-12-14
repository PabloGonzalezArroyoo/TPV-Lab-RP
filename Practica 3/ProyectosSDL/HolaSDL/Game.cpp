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

	// Máquina de estados
	gsm = new GameStateMachine();
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
	gsm->pushState(new MainMenuState(this));
	while (!exit) {
		render();
	}
	/*
	//Menu
	Menu* myMenu = dynamic_cast<Menu*> (*objects.begin());
	myMenu->render(); SDL_RenderPresent(renderer);			// Renderizado
	myMenu->run(); char answer = myMenu->getType();			// Procesado de input
	objects.pop_front(); delete(myMenu);					// Borrar memoria
	SDL_RenderClear(renderer);								// Limpiar pantalla

	if (answer == 'L') {									// Obtener usuario y cargar juego guardado
		string playerId = " ";
		cout << "Introduzca el codigo de la partida: ";
		cin >> playerId;
		loadFromFile(playerId);
	}

	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	lifeLeft();										// Mostrar info en la consola
	SDL_Delay(1500);
	while (!exit && !gameOver && !win) {
		handleEvents();								// Manejamos los eventos que puedan ocurrir
		
		frameTime = SDL_GetTicks() - startTime;		// Actualizamos cuanto tiempo ha pasado desde el ultimo frame
		if (frameTime >= FRAMERATE) {				// Comprobamos si el tiempo de frame es mayor al ratio
			update();								// Actualizamos el estado del juego
			startTime = SDL_GetTicks();				// Actualizamos el valor de nuestra variable al valor de este frame
		}
		render();									// Renderizamos
		if (!gameOver && !win) checkNextLevel(false);	// Comprobar si se ha pasado de nivel
	}

	if (gameOver || win) { render(); SDL_Delay(2000); }		// Tardamos en cerrar la ventana de SDL para que el jugador vea la pantalla final
	*/

	// CORRER MÁQUINA DE ESTADOS
	if (exit) cout << "\nSaliste del juego... bye!" << endl;
}

// Renderizado
void Game::render() {
	SDL_RenderClear(renderer);								// Limpiamos la pantalla

	gsm->currentState()->render();

	/*// Renderizado de los objetos del juego
	if (!gameOver && !win) {								// Si el juego no ha acabado
		for (list<ArkanoidObject*>::iterator it = objects.begin(); it != objects.end(); it++)
			if ((*it) != nullptr) (*it)->render();
	}
	// Renderizado de las pantallas de win o game over
	else {													// Si se ha perdido o ganado
		SDL_Rect dest;										// Creamos la ventana donde pintamos
		dest.w = WIN_WIDTH, dest.h = WIN_HEIGTH;			// Le damos sus dimensiones
		dest.x = dest.y = 0;								// Su posición es la esquina superior izquierda
		if (gameOver) textures[GameOver]->render(dest);		// Si el jugador ha perdido renderizamos la textura GameOver
		else textures[Winner]->render(dest);				// Si el jugador ha ganado renderizamos la textura Winner
	}*/

	// RENDER MÁQUINA DE ESTADOS
	SDL_RenderPresent(renderer);							// Pintamos
}

// Actualizar entidades
void Game::update() {
	// UPDATE MÁQUINA DE ESTADOS
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

// Pregunta por el código de usuario y llama al método de guardar en archivo
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

// Devuelve la textura correspondiente
Texture* Game::getTexture(int texture) {
	return textures[texture];
}