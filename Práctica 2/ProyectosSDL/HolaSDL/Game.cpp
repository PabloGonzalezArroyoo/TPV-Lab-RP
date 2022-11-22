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

	// Llenar el array de niveles con los niveles correspondientes y setear el nivel actual a 0
	levels[0] = "level01"; levels[1] = "level02"; levels[2] = "level03";
	// levels[0] = "cambioLvl"; levels[1] = "cambioLvl"; levels[2] = "cambioLvl"; -> Para llegar a la pantalla de victoria
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
	blockmap = new BlocksMap(winWidth - 2 * wallWidth, winHeight / 2 - wallWidth, textures[Blocks], levels[currentLevel]);
	objects.push_back(blockmap);
}

// Destructora
Game::~Game() {

	for (ArkanoidObject* myOb : objects) delete(myOb);
	objects.~list();

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
		if (!gameOver && !win) checkNextLevel();	// Comprobar si se ha pasado de nivel
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
	}
}

// Renderizado
void Game::render() {
	SDL_RenderClear(renderer);								// Limpiamos la pantalla

	if (!gameOver && !win) {								// Si el juego no ha acabado
		for (list<ArkanoidObject*>::iterator it = objects.begin(); it != objects.end(); it++) (*it)->render();
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
}

// Comprobar colisiones del Ball
bool Game::collidesBall(SDL_Rect rectBall, Vector2D& colV) {
	// Ball - Walls
	for (int i = 0; i < 3; i++) if (walls[i]->collidesW(rectBall, colV)) return true;

	// Ball - DeadLine
	if (rectBall.y >= winHeight - 10) { checkLife(); return true; }

	// Ball - Paddle // (RATIO, -2.5) -> Colisión con la paddle
	if (paddle->collidesP(rectBall, colV)) return true;

	// Ball - Blocks
	if (blockmap->collidesB(rectBall, colV)) {
		// No llamar a reward si nullptr
		return true;
	}
	return false;
}

// Comprobar colisiones del Reward
bool Game::collidesReward(SDL_Rect rectBall, char type) {
	return true;
}

void Game::createReward() {
	int random = 0 + (rand() % 30);
	char type = ' ';

	// Asignar char
	switch (random) {
	case 10: type = 'n';
		break;
	}

	// Si el type no es vacío, crear
}

// Comprobar si se ha pasado de nivel
void Game::checkNextLevel() {
	if (blockmap->getBlocks() == 0) {														// Si no hay bloques
		++currentLevel;																		// Actualizamos el nivel en el que estamos

		if (currentLevel >= nLevels) win = true;											// Si es el último nivel el jugador ha ganado
		else {																				// Si no es el último nivel
			blockmap->~BlocksMap();															// Eliminamos el mapa que acabamos de superar
			blockmap = new BlocksMap(winWidth - 2 * wallWidth, winHeight / 2 - wallWidth, textures[Blocks], levels[currentLevel]); // Creamos el nuevo mapa (el siguiente)

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