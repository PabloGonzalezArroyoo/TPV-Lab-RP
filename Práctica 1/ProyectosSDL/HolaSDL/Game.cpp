#include "Game.h"
#include "Vector2D.h"
//#include "Wall.h"
//#include "Ball.h"
//#include "Paddle.h"
#include "checkML.h"

Game::Game() {
	// Inicialización de la ventana
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks (Nos informa de la basura no gestionada)
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;

	gameOver = win = exit = false;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// To-DO cargar texturas
	for (int i = 0; i < nTextures; i++) {
		const TextureDescription& desc = textDescription[i];
		textures[i] = new Texture(renderer, desc.filename, desc.hframes, desc.vframes);
	}

	levels[0] = "level01"; levels[1] = "level02"; levels[2] = "level03";

	//Creamos paredes (punteros)
	walls[0] = new Wall(Vector2D(0, 0 + wallWidth), wallWidth, winHeight - wallWidth, textures[SideWall], Vector2D(1, 0));
	walls[1] = new Wall(Vector2D(winWidth - wallWidth, 0 + wallWidth), wallWidth, winHeight - wallWidth, textures[SideWall], Vector2D(-1, 0));
	walls[2] = new Wall(Vector2D(0, 0), winWidth, wallWidth, textures[TopWall], Vector2D(0, 1));
	//Creamos un puntero a la bola
	ball = new Ball(Vector2D(winWidth / 2 - wallWidth, winHeight - 50), Vector2D(1, -1), 15, 15, textures[BallTxt], this);
	//Creamos un puntero al paddle
	paddle = new Paddle(Vector2D(winWidth / 2 - wallWidth * 2, winHeight - 30), Vector2D(0, 0), 100, 10, textures[PaddleTxt], Vector2D(0, -1));
	
	//Creamos el mapas de bloques
	blockmap = new BlocksMap(winWidth - 2 * wallWidth, winHeight / 2 - wallWidth, textures[Blocks], levels[0]);
}

Game::~Game() {
	// Borrar Paddle
	paddle->~Paddle();
	delete(paddle);
	
	// Borrar Ball
	ball->~Ball();
	cout << "ballD" << endl;
	delete(ball);
	cout << "ballDD" << endl;

	// Borrar BlocksMap
	blockmap->~BlocksMap();
	cout << "blocksD" << endl;
	delete(blockmap);
	cout << "blocksDD" << endl;

	// Borrar Texturas
	for (int i = 0; i < nTextures; i++) { textures[i]->wipe(); delete(textures[i]); }
 	cout << "texturesDD" << endl;

	// Borrar render y window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	int level = 0;
	while (!exit && !gameOver && !win) {
		handleEvents();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= frameRate) {
			update();
			startTime = SDL_GetTicks();
		}
		if (blockmap->getBlocks() == 0 && level == levels->size()) win = true;
		else if (blockmap->getBlocks() == 0 && level != levels->size()) {
			++level;
			blockmap = new BlocksMap(winWidth - 2 * wallWidth, winHeight / 2 - wallWidth, textures[Blocks], levels[level]);
		}
		render();
	}

	if (gameOver || win) SDL_Delay(2000);
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		paddle->handleEvents(event);

		if (event.key.keysym.sym == SDLK_ESCAPE) exit = true;
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
	
	// Paddle
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