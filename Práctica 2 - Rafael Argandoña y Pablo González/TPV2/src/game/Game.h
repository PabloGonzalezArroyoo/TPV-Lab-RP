#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "../../../SDL2-2.0.7/include/SDL_error.h"
#include "../sdlutils/Music.h"
#include "../sdlutils/SoundEffect.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Vector2D.h"
#include "GameStateMachine.h"

#ifdef _WIN32
#include<windows.h>
#endif

const int NUM_TEXTURES = 3;
using namespace std;
typedef unsigned int uint;

class Game {
private:
	// Punteros SDL
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	Font* myFont;
	// Variables de flujo
	bool exit;

	// Texturas
	Texture* textures[NUM_TEXTURES];

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
	void refresh();

	// Getters
	Texture* getTexture(int texture);
	GameStateMachine* getStateMachine() { return gsm; };

	// Cambio de flujo para acabar el juego
	void changeControl() { exit = true; };
};