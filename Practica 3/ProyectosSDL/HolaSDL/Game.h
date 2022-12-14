// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "GameStateMachine.h"
#include "Vector2D.h"
#include "checkML.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

#ifdef _WIN32
	#include<windows.h>
#endif

using namespace std;
typedef unsigned int uint;

// Struct con el nombre y las dimensiones de frames del archivo
typedef struct {
	string filename;
	uint hframes, vframes;
} TextureDescription;

// Descripción de las texturas (según la estructura del struct anterior)
const TextureDescription textDescription[NUM_TEXTURES] = {
	{"ball2", 1, 1},
	{"bricks2", 2, 3},
	{"digits2", 3, 4},
	{"gameover1", 1, 1},
	{"paddle2", 1, 1},
	{"side", 1, 1},
	{"topside", 1, 1},
	{"youwin", 1, 1},
	{"rewards", 10, 8},
	{"menu", 1, 1},
	{"play", 1, 3},
	{"load", 1, 3},
	{"exit", 1, 3},
	{"resume", 1, 3},
	{"main", 1, 3},
	{"restart", 1, 3}
};

class PlayState;
class MainMenuState;
class PauseState;
class EndState;
class GameStateMachine;
class Game {
private:
	// Punteros SDL
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Variables de flujo
	bool exit;
	
	// Texturas
	Texture* textures[NUM_TEXTURES];

	// Máquina de estados
	GameStateMachine* gsm;

public:
	// Constructora (vacía y a partir de archivo) y destructora
	Game();
	~Game();

	// Métodos esenciales
	void run();
	void render();
	void update();
	void handleEvents();

	// Coger texturas
	Texture* getTexture(int texture);

	// Maquina de estados
	void newGame();
	void loadGame();
	void saveGame();
	void quit();
	void resume();
	void mainMenu();
	void pause();
};

