#include "Game.h"
#include "Vector2D.h"
#include "checkML.h"

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

	// To-DO cargar texturas
	for (int i = 0; i < nTextures; i++) {
		const TextureDescription& desc = textDescription[i];
		textures[i] = new Texture(renderer, desc.filename, desc.hframes, desc.vframes);
	}

	// Llenar el array de niveles con los niveles correspondientes y setear el nivel actual a 0
	levels[0] = "level01"; levels[1] = "level02"; levels[2] = "level03";
	currentLevel = 0;

	//Creamos paredes (punteros)
	walls[0] = new Wall(Vector2D(0, 0 + wallWidth), wallWidth, winHeight - wallWidth, textures[SideWall], Vector2D(1, 0));
	walls[1] = new Wall(Vector2D(winWidth - wallWidth, 0 + wallWidth), wallWidth, winHeight - wallWidth, textures[SideWall], Vector2D(-1, 0));
	walls[2] = new Wall(Vector2D(0, 0), winWidth, wallWidth, textures[TopWall], Vector2D(0, 1));

	//Creamos un puntero a la bola
	ball = new Ball(Vector2D(winWidth / 2 - wallWidth, winHeight - 50), Vector2D(1, -1), 15, 15, textures[BallTxt], this);

	//Creamos un puntero al paddle
	paddle = new Paddle(Vector2D(winWidth / 2 - wallWidth * 2, winHeight - 30), Vector2D(0, 0), 100, 10, textures[PaddleTxt]);
	
	//Creamos el mapas de bloques
	try { blockmap = new BlocksMap(winWidth - 2 * wallWidth, winHeight / 2 - wallWidth, textures[Blocks], levels[0]); }
	catch (string e) { throw e; }
}

// Destructora
Game::~Game() {
	// Borrar Paddle
	delete(paddle);
	
	// Borrar Ball
	delete(ball);

	// Borrar BlocksMap
	delete(blockmap);

	// Borrar Texturas
	for (int i = 0; i < nTextures; i++) { textures[i]->wipe(); delete(textures[i]); }

	// Borrar render y window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Bucle principal del juego
void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit && !gameOver && !win) {
		handleEvents();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= frameRate) {
			update();
			startTime = SDL_GetTicks();
		}
		render();
		checkNextLevel();						// Comprobar si se ha pasado de nivel
	}

	if (gameOver || win) SDL_Delay(2000);
}

// Comprobar si se ha pasado de nivel
void Game::checkNextLevel() {
	if (blockmap->getBlocks() == 0 && currentLevel == levels->size()) win = true;
	else if (blockmap->getBlocks() == 0 && currentLevel != levels->size()) {
		++currentLevel;
		blockmap->~BlocksMap();
		blockmap = new BlocksMap(winWidth - 2 * wallWidth, winHeight / 2 - wallWidth, textures[Blocks], levels[currentLevel]);
		ball->setPosition(Vector2D(winWidth / 2 - wallWidth, winHeight - 50), Vector2D(1, -1));
		SDL_Delay(1500);
	}
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.key.keysym.sym == SDLK_ESCAPE) exit = true;

		paddle->handleEvents(event, winWidth, wallWidth);
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	if (!gameOver && !win) {
		// Walls
		for (int i = 0; i < 3; i++) walls[i]->render();
		// Ball
		ball->render();
		// Paddle
		paddle->render();
		// BlockMap
		blockmap->render();
	}
	else {
		SDL_Rect dest;
		dest.w = 800, dest.h = 600;
		dest.x = dest.y = 0;
		if (gameOver) textures[GameOver]->render(dest);
		else textures[Winner]->render(dest);
	}
	
	SDL_RenderPresent(renderer);
}

void Game::update() {
	// Ball
	ball->update();
}

bool Game::collides(SDL_Rect rectBall, Vector2D& colV) {
	// Ball - Walls
	for (int i = 0; i < 3; i++) if (walls[i]->collidesW(rectBall, colV)) return true;

	// Ball - DeadLine
	if (rectBall.y >= winHeight - 10) gameOver = true;

	// Ball - Paddle // (RATIO, -2.5) -> Colisión con la paddle
	if (paddle->collidesP(rectBall, colV)) return true;

	// Ball - Blocks
	if (blockmap->collidesB(rectBall, colV)) return true;
	
	return false;
}