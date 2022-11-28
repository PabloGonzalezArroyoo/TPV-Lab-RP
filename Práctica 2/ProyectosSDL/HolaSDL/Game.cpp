// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#include "Game.h"
#include "Vector2D.h"

// Constructora
Game::Game() {
	// Inicialización de la ventana
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGTH, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw string("Error cargando SDL");

	// Variables de flujo
	gameOver = win = exit = false;

	// Para cargar texturas
	for (int i = 0; i < NUM_TEXTURES; i++) {
		const TextureDescription& desc = textDescription[i];
		textures[i] = new Texture(renderer, desc.filename, desc.hframes, desc.vframes);
	}

	// Poner el nivel actual a 0 y las vidas a su constante
	currentLevel = 0;
	life = NUM_LIFES;
	
	// Creamos paredes (punteros)
	walls[0] = new Wall(Vector2D(0, 0 + WALL_WIDTH), WALL_WIDTH, WIN_HEIGTH - WALL_WIDTH, textures[SideWall], Vector2D(1, 0));
	walls[1] = new Wall(Vector2D(WIN_WIDTH - WALL_WIDTH, 0 + WALL_WIDTH), WALL_WIDTH, WIN_HEIGTH - WALL_WIDTH, textures[SideWall], Vector2D(-1, 0));
	walls[2] = new Wall(Vector2D(0, 0), WIN_WIDTH, WALL_WIDTH, textures[TopWall], Vector2D(0, 1));
	objects.push_back(walls[0]);
	objects.push_back(walls[1]);
	objects.push_back(walls[2]);

	// Creamos un puntero a la bola
	ball = new Ball(Vector2D(WIN_WIDTH / 2 - WALL_WIDTH, WIN_HEIGTH - 50), 15, 15, textures[BallTxt], Vector2D(1, -1), this);
	objects.push_back(ball);

	// Creamos un puntero al paddle
	paddle = new Paddle(Vector2D(WIN_WIDTH / 2 - WALL_WIDTH * 2, WIN_HEIGTH - 30), 100, 10, textures[PaddleTxt], Vector2D(0, 0));
	objects.push_back(paddle);
	
	// Creamos el mapas de bloques
	ifstream in;
	in.open(levels[currentLevel] + ".dat");
	if (!in.is_open()) throw string("Error: couldn't load file (" + levels[currentLevel] + ".dat)"); // Si no se ha encontrado el archivo
	blockmap = new BlocksMap(WIN_WIDTH - 2 * WALL_WIDTH, WIN_HEIGTH / 2 - WALL_WIDTH, textures[Blocks], in);
	in.close();
	objects.push_back(blockmap);
	
	// Iteradores
	itBlocksMap = --(objects.end());
}

// Constructora a partir de archivo
Game::Game(string player) {
	// Inicialización de la ventana
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("ARKANOID", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGTH, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) throw string("Error cargando SDL");

	// Variables de flujo
	gameOver = win = exit = false;

	// Para cargar texturas
	for (int i = 0; i < NUM_TEXTURES; i++) {
		const TextureDescription& desc = textDescription[i];
		textures[i] = new Texture(renderer, desc.filename, desc.hframes, desc.vframes);
	}

	// Cargar archivo
	loadFromFile(player);
}

// Destructora
Game::~Game() {
	/*
	// Borrar Walss
	for (int i = 0; i < 3; i++) delete(walls[i]);

	// Borrar Paddle
	delete(paddle);
	
	// Borrar Ball
	delete(ball);

	// Borrar BlocksMap
	delete(blockmap);

	// Borrar Reward
	delete(reward);*/

	// Borrar Texturas
	for (int i = 0; i < NUM_TEXTURES; i++) delete(textures[i]);

	// Borrar lista
	for (ArkanoidObject* myOb : objects) delete(myOb);
	objects.~list();

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
		if (frameTime >= FRAMERATE) {				// Comprobamos si el tiempo de frame es mayor al ratio
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
		else paddle->handleEvents(event, WIN_WIDTH, WALL_WIDTH);// Si el evento es de otro tipo llamamos a la pala (por si son sus teclas de mov)
		
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
		dest.w = WIN_WIDTH, dest.h = WIN_HEIGTH;			// Le damos sus dimensiones
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
	if (rectBall.y >= WIN_HEIGTH - 10) { checkLife(); return true; }

	// Ball - Paddle // (RATIO, -2.5) -> Colisión con la paddle
	if (ball->getVelocity().getY() > 0) {										// Si la pelota estaba bajando
		if (paddle->collidesP(rectBall, colV)) return true;
	}

	// Ball - Blocks
	if (ball->getPosition().getY() <= WIN_HEIGTH / 2) {							// Si está por la zona del mapa
		if (blockmap->collidesB(rectBall, colV)) {
			if (reward == nullptr) createReward(blockmap->getDestroyedBlock()); // Crear reward si no existía de antes
			return true;
		}
	}
	return false;
}

// Comprobar colisiones del Reward
bool Game::collidesReward(SDL_Rect rectReward, char type) {
	if (rectReward.y >= WIN_HEIGTH)										// Si se sale de la pantalla
	{
		// Borrar
		reward->~Reward();
		reward = nullptr;
		objects.pop_back();

		// Confirmar colisión
		return true;
	}
	else if (SDL_HasIntersection(&rectReward, &(paddle->getRect()))) {	// Si colisiona con la pala
		// Comportamiento
		rewardBehaviour(type);

		// Borrar
		reward->~Reward();
		reward = nullptr;
		objects.pop_back();

		// Confirmar colisión
		return true;
	}
	return false;														// Negar colisión
}

// Crear reward en base a posibilidades
void Game::createReward(Vector2D rPos) {
	// Número aleatorio en un rango
	int random = 0 + (rand() % 40);
	random %= 8;
	
	// Asignar tipo
	char type = 'x';
	switch (random) {
		case 0: type = 'L'; break;
		case 1: type = 'R'; break;
		case 2: type = 'E'; break;
		case 3: type = 'S'; break;
	}

	// Si no es de tipo vacío, instanciarlo y añadirlo a la lista
	if (type != 'x') {
		reward = new Reward(rPos, 35, 20, textures[Rewards], Vector2D(0, 1), type, this);
		objects.push_back(reward);
	}
}

// Llama al comportamiento correspondiente al reward recibido
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

		if (currentLevel >= NUM_LEVELS) win = true;											// Si es el último nivel el jugador ha ganado
		else {																				// Si no es el último nivel
			blockmap->~BlocksMap();															// Eliminamos el mapa que acabamos de superar
			ifstream in;
			in.open(levels[currentLevel] + ".dat");
			if (!in.is_open()) throw string("Error: couldn't load file (" + levels[currentLevel] + ".dat)"); // Si no se ha encontrado el archivo
			blockmap = new BlocksMap(WIN_WIDTH - 2 * WALL_WIDTH, WIN_HEIGTH / 2 - WALL_WIDTH, textures[Blocks], in); // Creamos el nuevo mapa (el siguiente)
			in.close();
			*itBlocksMap = blockmap;

			ball->setPosition(Vector2D(WIN_WIDTH / 2 - WALL_WIDTH, WIN_HEIGTH - 50), Vector2D(1, -1)); // Movemos la pelota a la posición inicial del juego
			paddle->setPosition(Vector2D(WIN_WIDTH / 2 - WALL_WIDTH * 2, WIN_HEIGTH - 30), Vector2D(0, 0)); // Movemos la pala a la posición inicial del juego
			SDL_Delay(1500);																// Al cambiar de nivel tardamos en actualizar la pantalla
		}
	}
}

// Gestionar vida: quitar un punto de vida y resetear posiciones de entidades
void Game::checkLife() {
	--life;											// Decrementamos la vida							
	if (life <= 0) gameOver = true;					// Si no quedan vidas, fin de la partida
	else {											// Si quedan, resetear la posición inicial la pala y la pelota
		ball->setPosition(Vector2D(WIN_WIDTH / 2 - WALL_WIDTH, WIN_HEIGTH - 50), Vector2D(1, -1)); // Movemos la pelota a la posición inicial del juego
		paddle->setPosition(Vector2D(WIN_WIDTH / 2 - WALL_WIDTH * 2, WIN_HEIGTH - 30), Vector2D(0, 0)); // Movemos la pala a la posición inicial del j
	}
	lifeLeft();										// Mostrar info en la consola
}

// Muestra en consola la vida actual
void Game::lifeLeft() {
	// Borrar consola según SO
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif

	cout << "VIDAS RESTANTES: " << life << endl;	// Escribir en consola
}

// Guardar en arhivo
void Game::saveToFile(string filename) {
	ofstream out;
	out.open("saves/" + filename + ".txt");

	// Guardar objetos de la lista de objetos
	for (list<ArkanoidObject*>::iterator it = objects.begin(); it != objects.end(); it++) {
		(*it)->saveToFile(out); out << endl;
	}

	// Guardar nivel actual y vida
	out << "L " << currentLevel << endl;	// 'L' usado para determinar si existe o no un reward en la lectura
	out << life;

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
	if (!in.is_open()) throw string("Error: couldn't load file (" + filename + ")"); // Si no se ha encontrado el archivo
	
	// Paredes
	walls[0] = new Wall(); walls[0]->loadFromFile(in, textures[SideWall]); objects.push_back(walls[0]);
	walls[1] = new Wall(); walls[1]->loadFromFile(in, textures[SideWall]); objects.push_back(walls[1]);
	walls[2] = new Wall(); walls[2]->loadFromFile(in, textures[TopWall]); objects.push_back(walls[2]);

	// Pelota
	ball = new Ball(); ball->loadFromFile(in, textures[BallTxt]);
	ball->setGameDepend(this); objects.push_back(ball);

	// Pala
	paddle = new Paddle(); paddle->loadFromFile(in, textures[PaddleTxt]); objects.push_back(paddle);

	// Mapa de bloques
	blockmap = new BlocksMap(WIN_WIDTH - 2 * WALL_WIDTH, WIN_HEIGTH / 2 - WALL_WIDTH, textures[Blocks], in);
	objects.push_back(blockmap); itBlocksMap = --(objects.end());

	// Reward si existe
	char rExists = ' ';
	in >> rExists;
	if (rExists == '{') {			// Si existe un carcáter '{' antes de leer los niveles y la vida, es que existe la reward
		reward = new Reward(); reward->loadFromFile(in, textures[Rewards]);
		reward->setGameDepend(this); objects.push_back(reward);
	}

	// Leer nivel actual y vida
	in >> currentLevel;
	in >> life;

	in.close();
}