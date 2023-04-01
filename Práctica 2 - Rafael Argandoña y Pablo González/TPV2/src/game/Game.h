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

using namespace std;
typedef unsigned int uint;

class Game {
private:
	// Punteros SDL
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Variables de flujo
	bool exit;

	// Máquina de estados
	GameStateMachine* gsm;

public:
	// Constructora y destructora
	Game();
	~Game();

	// Métodos esenciales
	void run();
	void update();
	void refresh();

	// Getters
	GameStateMachine* getStateMachine() { return gsm; };

	// Cambio de flujo para acabar el juego
	void changeControl() { exit = true; };
};