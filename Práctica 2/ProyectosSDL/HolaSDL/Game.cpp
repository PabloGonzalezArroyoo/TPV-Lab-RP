// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#include "Game.h"
#include "Vector2D.h"

// Constructora
Game::Game() {
	// Inicialización de la ventana
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("ARKANOID V2", SDL_WINDOWPOS_CENTERED,
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
	currentLevel = 0; life = NUM_LIFES;
	
	//Añadimos el mapa de bloques
	ifstream in;
	in.open(levels[currentLevel] + ".dat");
	if (!in.is_open()) throw string("Error: couldn't load file (" + levels[currentLevel] + ".dat)"); // Si no se ha encontrado el archivo
	objects.push_back(new BlocksMap(WIN_WIDTH - 2 * WALL_WIDTH, WIN_HEIGTH / 2 - WALL_WIDTH, textures[Blocks], in));
	in.close();

	//Añadimos las paredes
	objects.push_back(new Wall(Vector2D(0, 0 + WALL_WIDTH), WALL_WIDTH, WIN_HEIGTH - WALL_WIDTH, textures[SideWall], Vector2D(1, 0)));
	objects.push_back(new Wall(Vector2D(WIN_WIDTH - WALL_WIDTH, 0 + WALL_WIDTH), WALL_WIDTH, WIN_HEIGTH - WALL_WIDTH, textures[SideWall], Vector2D(-1, 0)));
	objects.push_back(new Wall(Vector2D(0, 0), WIN_WIDTH, WALL_WIDTH, textures[TopWall], Vector2D(0, 1)));

	//Añadimos la plataforma
	objects.push_back(new Paddle(Vector2D(WIN_WIDTH / 2 - WALL_WIDTH * 2, WIN_HEIGTH - 30), 100, 10, textures[PaddleTxt], Vector2D(0, 0)));

	//Añadimos la pelota
	objects.push_back(new Ball(Vector2D(WIN_WIDTH / 2 - WALL_WIDTH, WIN_HEIGTH - 50), 15, 15, textures[BallTxt], Vector2D(1, -1), this));
	
	// Iteradores
	itBall = prev(objects.end());

	//Creamos el menu
	objects.push_front(new Menu(Vector2D(), WIN_WIDTH, WIN_HEIGTH, textures[MainMenu]));
}

// Destructora
Game::~Game() {
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
		else (*(prev(itBall)))->handleEvent(event);				// Si el evento es de otro tipo llamamos a la pala (por si son sus teclas de mov)
		
		if (event.key.keysym.sym == SDLK_s) userSaving();		// Guardar
	}
}

// Renderizado
void Game::render() {
	SDL_RenderClear(renderer);								// Limpiamos la pantalla

	// Renderizado de los objetos del juego
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
	}

	SDL_RenderPresent(renderer);							// Pintamos
}

// Actualizar entidades
void Game::update() {
	// Desde el anterior a ball (pala) hasta el final (contando rewards si existen)
	for (list<ArkanoidObject*>::iterator it = prev(itBall); it != objects.end(); it++) {
		(*it)->update();
	}
}

// Comprobar colisiones del Ball
bool Game::collidesBall(SDL_Rect rectBall, Vector2D& colV) {
	// Ball - DeadLine
	if (rectBall.y >= WIN_HEIGTH - 10) { checkLife(); return true; }

	list<ArkanoidObject*>::iterator it = objects.begin();				// Inicializar iterador para recorrer la lista
	
	// Ball - Blocksmap
	if (rectBall.y <= WIN_HEIGHT / 2) {
		if ((*it)->collides(rectBall, colV)) {
			BlocksMap* myBm = dynamic_cast<BlocksMap*> (*it);
			createReward(myBm->getDestroyedBlock());
			return true;
		}
	}

	// Ball - Walls
	++it;
	for (int i = 0; i < 3; ++i) {
		if ((*it)->collides(rectBall, colV)) return true;
		else ++it;
	}

	// Ball - Paddle
	Ball* myBall = dynamic_cast<Ball*> (* itBall);
	if (rectBall.y > WIN_HEIGHT - 50 && myBall->getVelocity().getY() > 0) {
		if ((*it)->collides(rectBall, colV)) return true;
	}

	return false;
}

// Comprobar colisiones del Reward
bool Game::collidesReward(SDL_Rect rectReward, char type, Reward* rew) {
	if (rectReward.y >= WIN_HEIGTH)										// Si se sale de la pantalla
	{
		/*
		// Borrar
		reward->~Reward();
		reward = nullptr;
		objects.pop_back();

		

		// Confirmar colisión
		return true;*/
	}
	else if (SDL_HasIntersection(&rectReward, &((prev(*itBall))->getRect()))) {	// Si colisiona con la pala
		// Comportamiento
		/*
		rewardBehaviour(type);

		// Borrar
		reward->~Reward();
		reward = nullptr;
		objects.pop_back();

		// Confirmar colisión
		return true;*/
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
		objects.push_back(new Reward(rPos, 35, 20, textures[Rewards], Vector2D(0, 1), type, this));
	}
}

// Llama al comportamiento correspondiente al reward recibido
void Game::rewardBehaviour(char type){
	Paddle* myPaddle = dynamic_cast<Paddle*> (prev(*itBall));
	switch (type) {
		case 'L': checkNextLevel(true); break;					// Cambio de nivel
		case 'R': ++life; lifeLeft(); break;					// +1 de vida
		case 'E': myPaddle->changeDimensions(true); break;		// Alargar pala
		case 'S': myPaddle->changeDimensions(false); break;		// Acortar pala
	}
}

// Comprobar si se ha pasado de nivel
void Game::checkNextLevel(bool rewardAct) {
	BlocksMap* myBm = dynamic_cast<BlocksMap*> (* (objects.begin()));

	if (myBm->getBlocks() == 0 || rewardAct) {												// Si no hay bloques
		++currentLevel;																		// Actualizamos el nivel en el que estamos

		if (currentLevel >= NUM_LEVELS) win = true;											// Si es el último nivel el jugador ha ganado
		else {																				// Si no es el último nivel
			myBm->~BlocksMap();																// Eliminamos el mapa que acabamos de superar
			ifstream in;
			in.open(levels[currentLevel] + ".dat");
			if (!in.is_open()) throw string("Error: couldn't load file (" + levels[currentLevel] + ".dat)"); // Si no se ha encontrado el archivo
			myBm = new BlocksMap(WIN_WIDTH - 2 * WALL_WIDTH, WIN_HEIGTH / 2 - WALL_WIDTH, textures[Blocks], in); // Creamos el nuevo mapa (el siguiente)
			in.close();
			objects.pop_front();
			objects.push_front(myBm);

			reloadItems();																	// Volver los items a su posición inicial
			SDL_Delay(1500);																// Al cambiar de nivel tardamos en actualizar la pantalla
		}
	}
}

// Gestionar vida: quitar un punto de vida y resetear posiciones de entidades
void Game::checkLife() {
	--life;											// Decrementamos la vida							
	if (life <= 0) gameOver = true;					// Si no quedan vidas, fin de la partida
	else reloadItems();								// Si quedan, resetear la posición inicial la pala y la pelota
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

	// Escribir en consola
	cout << "VIDAS RESTANTES: " << life << endl;
}

// Vuelve los items a su estado inicial (p.ej: cuando se pierde una vida)
void Game::reloadItems() {

	// Borra los items presentes en partida
	for (list<ArkanoidObject*>::iterator it = prev(objects.end()); it != itBall; --it) {
		delete(*it);
		objects.pop_back();
	}

	// Poner la bola y la pala en las posiciones y velocidades inciales
	Ball* myBall = dynamic_cast<Ball*> (*itBall);
	Paddle* myPaddle = dynamic_cast<Paddle*> (prev(*itBall));
	myBall->setPosition(Vector2D(WIN_WIDTH / 2 - WALL_WIDTH, WIN_HEIGTH - 50), Vector2D(1, -1)); // Movemos la pelota a la posición inicial del juego
	myPaddle->setPosition(Vector2D(WIN_WIDTH / 2 - WALL_WIDTH * 2, WIN_HEIGTH - 30), Vector2D(0, 0)); // Movemos la pala a la posición inicial del juego
}

// Guardar en arhivo
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
	if (!in.is_open()) throw string("Error: couldn't load file (" + filename + ")"); // Si no se ha encontrado el archivo

	// Vaciar la lista anterior
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