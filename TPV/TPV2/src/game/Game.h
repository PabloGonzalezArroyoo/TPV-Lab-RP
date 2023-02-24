#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "GameStateMachine.h"
#include "../utils/Vector2D.h"
#include "../utils/chekML.h"
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



class Game {
private:
	// Punteros SDL
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Variables de flujo
	bool exit;

	// Texturas
	//Texture* textures[NUM_TEXTURES];

	// Máquina de estados
	GameStateMachine* gsm;

public:
	// Constructora y destructora
	Game();
	~Game();

	// Métodos esenciales
	void run();
	void render();
	void update();
	void handleEvents();

	// Getters
	//Texture* getTexture(int texture);
	GameStateMachine* getStateMachine() { return gsm; };
	void changeControl() { exit = true; };

	// Maquina de estados
	void saveGame();
};