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
		cout << i << " " << "fil: " << desc.hframes << " col: " << desc.vframes;
		textures[i] = new Texture(renderer, desc.filename, desc.hframes, desc.vframes);
	}

	//Creamos paredes (punteros)
	walls[0] = new Wall(Vector2D(0, 0 + wallWidth), wallWidth, winHeight - wallWidth, textures[SideWall], Vector2D(1, 0));
	walls[1] = new Wall(Vector2D(winWidth - wallWidth, 0 + wallWidth), wallWidth, winHeight - wallWidth, textures[SideWall], Vector2D(-1, 0));
	walls[2] = new Wall(Vector2D(0, 0), winWidth, wallWidth, textures[TopWall], Vector2D(0, 1));
	//Creamos un puntero a la bola
	ball = new Ball(Vector2D(winWidth / 2, winHeight - 50), Vector2D(1, -1), 15, 15, textures[BallTxt], this);
	//Creamos un puntero al paddle
	paddle = new Paddle(Vector2D(winWidth / 2 - 25, 3 * winHeight / 4), 60, 10, Vector2D(0, 0), textures[PaddleTxt]);

	//Creamos el mapas de bloques
	blockmap = new BlocksMap(winWidth - 2 * wallWidth, winHeight / 2 - wallWidth, textures[Blocks]);
}

Game::~Game() {
	// delete(paddle);
	delete(ball);
	// delete(blockmap);
	for (int i = 0; i < nTextures; i++) { textures[i]->wipe(); delete(textures[i]); }

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

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
	}
}

void Game::handleEvents() {

}

void Game::render() {
	SDL_RenderClear(renderer);

	// To-DO
	// Walls
	for (int i = 0; i < 3; i++) {
		walls[i]->render();
	}
	
	// Ball
	ball->render();
	// Paddle
	paddle->render();
	// BlockMap
	blockmap->render();
	// Idea: punteros únicos a los distintos objetos
	SDL_RenderPresent(renderer);
}

void Game::update() {
	// Ball
	//ball->update();
	
	// Paddle
}
bool Game::collides(SDL_Rect rectBall, Vector2D& colV) {
	// Ball - Walls
	for (int i = 0; i < 3; i++) {
		if (walls[0]->collides(rectBall, colV)) return true;
	}

	// Ball - Paddle // (RATIO, -2.5) -> Colisión con la paddle

	// Ball - Blocks

	// Ball - DeadLine
	if (rectBall.y >= winHeight - 10) return true;

	return false;
}