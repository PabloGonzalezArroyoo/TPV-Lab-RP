#include "Game.h"
#include "Vector2D.h"
#include "Wall.h"
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

	walls[0] = Wall(Vector2D(0, 0), wallWidth, winHeight, textures[SideWall]);
	walls[1] = Wall(Vector2D(winWidth - 15, 0), wallWidth, winHeight, textures[SideWall]);
	walls[2] = Wall(Vector2D(0 + 15, 0), wallWidth, winHeight, textures[TopWall]);
}

Game::~Game() {
	// delete(paddle);
	// delete(ball);
	// delete(blockmap);
	for (int i = 0; i < nTextures; i++) delete(textures[i]);

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
		cout << "hellothere";
		walls[i].render();
	}
	// Ball
	//ball->render();
	// Paddle
	//paddle->render();
	// BlockMap
	//blockmap->render();
	// Idea: punteros únicos a los distintos objetos
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
}

void Game::update() {}
void Game::collides() {}