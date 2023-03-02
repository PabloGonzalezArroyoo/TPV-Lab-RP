#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "GameStateMachine.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/Texture.h"
#include "../utils/chekML.h"
#include "../sdlutils/InputHandler.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include "../../../SDL2-2.0.7/include/SDL_error.h"
#include "../sdlutils/Music.h"
#include "../sdlutils/SoundEffect.h"

#ifdef _WIN32
#include<windows.h>
#endif

const int NUM_TEXTURES = 8;
using namespace std;
typedef unsigned int uint;

// Struct con el nombre y las dimensiones de frames del archivo
typedef struct {
	string filename;
	uint hframes, vframes;
} TextureDescription;

// Descripción de las texturas (según la estructura del struct anterior)
const TextureDescription textDescription[NUM_TEXTURES - 3] = {
	// Objetos
	{"fighter", 1, 1},
	{"asteroid_gold", 5, 6},
	{"asteroid", 5, 6},
	{"fire", 1, 1},
	{"heart", 1, 1}
};

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
	void changeControl() { exit = true; };
};