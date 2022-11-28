// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#include "Game.h"
#include "Vector2D.h"

// Constructora
Game::Game() {
	// Inicialización de la ventana
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw string("Error cargando SDL");

	// Variables de flujo
	gameOver = win = exit = false;

	// Para cargar texturas
	for (int i = 0; i < nTextures; i++) {
		const TextureDescription& desc = textDescription[i];
		textures[i] = new Texture(renderer, desc.filename, desc.hframes, desc.vframes);
	}

	// Poner el nivel actual a 0
	currentLevel = 0;
	
	// Creamos paredes (punteros)
	walls[0] = new Wall(Vector2D(0, 0 + wallWidth), wallWidth, winHeight - wallWidth, textures[SideWall], Vector2D(1, 0));
	walls[1] = new Wall(Vector2D(winWidth - wallWidth, 0 + wallWidth), wallWidth, winHeight - wallWidth, textures[SideWall], Vector2D(-1, 0));
	walls[2] = new Wall(Vector2D(0, 0), winWidth, wallWidth, textures[TopWall], Vector2D(0, 1));
	objects.push_back(walls[0]);
	objects.push_back(walls[1]);
	objects.push_back(walls[2]);

	// Creamos un puntero a la bola
	ball = new Ball(Vector2D(winWidth / 2 - wallWidth, winHeight - 50), 15, 15, textures[BallTxt], Vector2D(1, -1), this);
	objects.push_back(ball);

	// Creamos un puntero al paddle
	paddle = new Paddle(Vector2D(winWidth / 2 - wallWidth * 2, winHeight - 30), 100, 10, textures[PaddleTxt], Vector2D(0, 0));
	objects.push_back(paddle);
	
	// Creamos el mapas de bloques
	ifstream in;
	in.open(levels[currentLevel] + ".dat");
	if (!in.is_open()) throw string("Error: couldn't load file (" + levels[currentLevel] + ".dat)"); // Si no se ha encontrado el archivo
	blockmap = new BlocksMap(winWidth - 2 * wallWidth, winHeight / 2 - wallWidth, textures[Blocks], in);
	in.close();
	objects.push_back(blockmap);
	
	// Iteradores
	itBlocksMap = --(objects.end());
}

Game::Game(string player) {
	// Inicialización de la ventana
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("ARKANOID", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw string("Error cargando SDL");

	// Variables de flujo
	gameOver = win = exit = false;

	// Para cargar texturas
	for (int i = 0; i < nTextures; i++) {
		const TextureDescription& desc = textDescription[i];
		textures[i] = new Texture(renderer, desc.filename, desc.hframes, desc.vframes);
	}

	loadFromFile(player);
}

// Destructora
Game::~Game() {
	// Borrar lista
	for (ArkanoidObject* myOb : objects) delete(myOb);
	objects.~list();

	// Borrar Walss
	for (int i = 0; i < 3; i++) delete(walls[i]);

	// Borrar Paddle
	delete(paddle);
	
	// Borrar Ball
	delete(ball);

	// Borrar BlocksMap
	delete(blockmap);

	// Borrar Texturas
	for (int i = 0; i < nTextures; i++) delete(textures[i]);

	// Borrar render y window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Bucle principal del juego
void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	lifeLeft();										// Mostrar info en la consola
	while (!exit && !gameOver && !win) {
		handleEvents();								// Manejamos los eventos que puedan ocurrir
		
		frameTime = SDL_GetTicks() - startTime;		// Actualizamos cuanto tiempo ha pasado desde el ultimo frame
		if (frameTime >= frameRate) {				// Comprobamos si el tiempo de frame es mayor al ratio
			update();								// Actualizamos el estado del juego
			startTime = SDL_GetTicks();				// Actualizamos el valor de nuestra variable al valor de este frame
		}
		render();									// Renderizamos
		if (!gameOver && !win) checkNextLevel(false);	// Comprobar si se ha pasado de nivel
	}

	if (gameOver || win) { render(); SDL_Delay(2000); }		// Tardamos en cerrar la ventana de SDL para que el jugador vea la pantalla final
	if (exit) cout << "\nSaliste del juego... bye!" << endl;
}

// Manejar eventos (pulsar teclas...)
void Game::handleEvents() {
	SDL_Event event;											// Creamos un evento
	while (SDL_PollEvent(&event)) {								// Mientras haya un evento en espera
		if (event.key.keysym.sym == SDLK_ESCAPE) exit = true;	// Si el jugador ha pulsado ESCAPE, se cierra el juego
		else paddle->handleEvents(event, winWidth, wallWidth);	// Si el evento es de otro tipo llamamos a la pala (por si son sus teclas de mov)
		
		if (event.key.keysym.sym == SDLK_s) userSaving();		// Guardar
	}
}

// Renderizado
void Game::render() {
	SDL_RenderClear(renderer);								// Limpiamos la pantalla

	if (!gameOver && !win) {								// Si el juego no ha acabado
		for (list<ArkanoidObject*>::iterator it = objects.begin(); it != objects.end(); it++)
			if ((*it) != nullptr) (*it)->render();
	}
	else {													// Si se ha perdido o ganado
		SDL_Rect dest;										// Creamos la ventana donde pintamos
		dest.w = winWidth, dest.h = winHeight;				// Le damos sus dimensiones
		dest.x = dest.y = 0;								// Su posición es la esquina superior izquierda
		if (gameOver) textures[GameOver]->render(dest);		// Si el jugador ha perdido renderizamos la textura GameOver
		else textures[Winner]->render(dest);				// Si el jugador ha ganado renderizamos la textura Winner
	}
	SDL_RenderPresent(renderer);							// Pintamos
}

// Actualizar entidades
void Game::update() {
	// Ball
	ball->update();

	if (reward != nullptr) reward->update();
}

// Comprobar colisiones del Ball
bool Game::collidesBall(SDL_Rect rectBall, Vector2D& colV) {
	// Ball - Walls
	for (int i = 0; i < 3; i++) if (walls[i]->collidesW(rectBall, colV)) return true;

	// Ball - DeadLine
	if (rectBall.y >= winHeight - 10) { checkLife(); return true; }

	// Ball - Paddle // (RATIO, -2.5) -> Colisión con la paddle
	if (ball->getVelocity().getY() > 0) {
		if (paddle->collidesP(rectBall, colV)) return true;
	}

	// Ball - Blocks
	if (ball->getPosition().getY() <= winHeight / 2) {
		if (blockmap->collidesB(rectBall, colV)) {
			if (reward == nullptr) createReward(blockmap->getDestroyedBlock());
			return true;
		}
	}
	return false;
}

// Comprobar colisiones del Reward
bool Game::collidesReward(SDL_Rect rectReward, char type) {
	if (rectReward.y >= winHeight)
	{
		reward->~Reward();
		reward = nullptr;
		objects.pop_back();
		return true;
	}
	else if (SDL_HasIntersection(&rectReward, &(paddle->getRect()))) {
		rewardBehaviour(type);
		reward->~Reward();
		reward = nullptr;
		objects.pop_back();
		return true;
	}
	return false;
}

// Crear reward en base a posibilidades
void Game::createReward(Vector2D rPos) {
	int random = 0 + (rand() % 40);					// Número aleatorio en un rango
	char type = 'x';
	random %= 8;
	// Asignar tipo
	switch (random) {
		case 0: type = 'L'; break;
		case 1: type = 'R'; break;
		case 2: type = 'E'; break;
		case 3: type = 'S'; break;
	}

	if (type != 'x') {
		reward = new Reward(rPos, 35, 20, textures[Rewards], Vector2D(0, 1), type, this);
		objects.push_back(reward);
	}
}

void Game::rewardBehaviour(char type){
	switch (type) {
		case 'L': checkNextLevel(true); break;
		case 'R': ++life; lifeLeft(); break;
		case 'E': paddle->changeDimensions(true); break;
		case 'S': paddle->changeDimensions(false); break;
	}
}

// Comprobar si se ha pasado de nivel
void Game::checkNextLevel(bool rewardAct) {
	if (blockmap->getBlocks() == 0 || rewardAct) {														// Si no hay bloques
		++currentLevel;																		// Actualizamos el nivel en el que estamos

		if (currentLevel >= nLevels) win = true;											// Si es el último nivel el jugador ha ganado
		else {																				// Si no es el último nivel
			blockmap->~BlocksMap();															// Eliminamos el mapa que acabamos de superar
			ifstream in;
			in.open(levels[currentLevel] + ".dat");
			if (!in.is_open()) throw string("Error: couldn't load file (" + levels[currentLevel] + ".dat)"); // Si no se ha encontrado el archivo
			blockmap = new BlocksMap(winWidth - 2 * wallWidth, winHeight / 2 - wallWidth, textures[Blocks], in); // Creamos el nuevo mapa (el siguiente)
			in.close();
			*itBlocksMap = blockmap;

			ball->setPosition(Vector2D(winWidth / 2 - wallWidth, winHeight - 50), Vector2D(1, -1)); // Movemos la pelota a la posición inicial del juego
			paddle->setPosition(Vector2D(winWidth / 2 - wallWidth * 2, winHeight - 30), Vector2D(0, 0)); // Movemos la pala a la posición inicial del juego
			SDL_Delay(1500);																// Al cambiar de nivel tardamos en actualizar la pantalla
		}
	}
}

// Gestionar vida: quitar un punto de vida y resetear posiciones de entidades
void Game::checkLife() {
	--life;											// Decrementamos la vida							
	if (life <= 0) gameOver = true;					// Si no quedan vidas, fin de la partida
	else {											// Si quedan, resetear la posición inicial la pala y la pelota
		ball->setPosition(Vector2D(winWidth / 2 - wallWidth, winHeight - 50), Vector2D(1, -1)); // Movemos la pelota a la posición inicial del juego
		paddle->setPosition(Vector2D(winWidth / 2 - wallWidth * 2, winHeight - 30), Vector2D(0, 0)); // Movemos la pala a la posición inicial del j
	}
	lifeLeft();										// Mostrar info en la consola
}

// Muestra en consola la vida actual
void Game::lifeLeft() {
	cout << "VIDAS RESTANTES: " << life << endl;	// Escribir en consola
}

// Guardar en arhivo
void Game::saveToFile(string filename) {
	ofstream out1;
	out1.open("saves/" + filename + ".txt");

	for (list<ArkanoidObject*>::iterator it = objects.begin(); it != objects.end(); it++) {
		(*it)->saveToFile(out1); out1 << endl;
	}

	out1 << "L " << currentLevel;

	out1.close();
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
	if (!in.is_open()) throw string("Error: couldn't load file (" + filename + ")"); // Si no se ha encontrado el archivo
	
	walls[0] = new Wall(); walls[0]->loadFromFile(in, textures[SideWall]); objects.push_back(walls[0]);
	walls[1] = new Wall(); walls[1]->loadFromFile(in, textures[SideWall]); objects.push_back(walls[1]);
	walls[2] = new Wall(); walls[2]->loadFromFile(in, textures[TopWall]); objects.push_back(walls[2]);

	ball = new Ball(); ball->loadFromFile(in, textures[BallTxt]);
	ball->setGameDepend(this); objects.push_back(ball);

	paddle = new Paddle(); paddle->loadFromFile(in, textures[PaddleTxt]); objects.push_back(paddle);

	blockmap = new BlocksMap(winWidth - 2 * wallWidth, winHeight / 2 - wallWidth, textures[Blocks], in);
	objects.push_back(blockmap); itBlocksMap = --(objects.end());

	char rExists = ' ';
	in >> rExists;
	if (rExists == '{') {
		reward = new Reward(); 
		reward->loadFromFile(in, textures[Rewards]);
		reward->setGameDepend(this);
		objects.push_back(reward);

	}

	in >> currentLevel;

	in.close();
}