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
#include "../utils/chekML.h"
#include "GameStateMachine.h"

#ifdef _WIN32
#include<windows.h>
#endif

const int NUM_TEXTURES = 8;
const int NUM_SOUNDS = 5;
const int NUM_MUSIC = 1;
using namespace std;
typedef unsigned int uint;

// Struct con el nombre y las dimensiones de frames del archivo
typedef struct {
	string filename;
	uint hframes, vframes;
} TextureDescription;

// Descripci�n de las texturas (seg�n la estructura del struct anterior)
const TextureDescription textDescription[NUM_TEXTURES - 3] = {
	// Objetos
	{"fighter", 1, 1},
	{"asteroid_gold", 5, 6},
	{"asteroid", 5, 6},
	{"fire", 1, 1},
	{"heart", 1, 1}
};

// Nombres de los sonidos del juego 
const string soundsDescription[NUM_SOUNDS] = {
	"explosion",
	"fire",
	"oof",
	"select",
	"thrust"
};

// Nombres de la m�sica del juego
const string musicDescription[NUM_MUSIC] = {
	"galaxy"
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

	// Sonidos
	SoundEffect* sounds[NUM_SOUNDS];

	// M�sica
	Music* music[NUM_MUSIC];

	// M�quina de estados
	GameStateMachine* gsm;

public:
	// Constructora y destructora
	Game();
	~Game();

	// M�todos esenciales
	void run();
	void render();
	void update();
	void refresh();

	// Getters
	Texture* getTexture(int texture);
	SoundEffect* getSound(int sound);
	Music* getMusic(int _music);
	GameStateMachine* getStateMachine() { return gsm; };

	// Cambio de flujo para acabar el juego
	void changeControl() { exit = true; };
};