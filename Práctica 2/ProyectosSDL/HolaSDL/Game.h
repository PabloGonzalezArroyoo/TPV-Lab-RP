// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Paddle.h"
#include "Ball.h"
#include "BlocksMap.h"
#include "Wall.h"
#include "Reward.h"
#include "Menu.h"
#include "checkML.h"
#include <iostream>
#include <fstream>
#include <list>
#ifdef _WIN32
	#include<windows.h>
#endif

using namespace std;
typedef unsigned int uint;

// Constantes
const uint WIN_WIDTH = 800;
const uint WIN_HEIGTH = 600;
const uint FRAMERATE = 10;
const uint NUM_TEXTURES = 10;
const uint NUM_LEVELS = 3;
const uint NUM_LIFES = 1;

// Enum con el nº de la textura correspondiente dentro del array
enum TextureName {BallTxt, Blocks, Digits, GameOver, PaddleTxt, SideWall, TopWall, Winner, Rewards, MainMenu};

// Struct con el nombre y las dimensiones de frames del archivo
typedef struct {
	string filename;
	uint hframes, vframes;
} TextureDescription;

// Descripción de las texturas (según la estructura del struct anterior)
const TextureDescription textDescription[NUM_TEXTURES] = {
	{"../images/ball2.png", 1, 1},
	{"../images/bricks2.png", 2, 3},
	{"../images/digits2.png", 3, 4},
	{"../images/gameover1.png", 1, 1},
	{"../images/paddle2.png", 1, 1},
	{"../images/side.png", 1, 1},
	{"../images/topside.png", 1, 1},
	{"../images/youwin.png", 1, 1},
	{"../images/rewards.png", 10, 8},
	{"../images/Menu.png", 1, 1}
};

class Game {
private:
	// Punteros SDL
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Variables de flujo
	bool exit, gameOver, win;
	
	// Texturas
	Texture* textures[NUM_TEXTURES];

	// Lista polimórfica
	list<ArkanoidObject*> objects;
	list<ArkanoidObject*>::iterator itBall;

	// Niveles
	string levels[NUM_LEVELS] = { "level01", "level02", "level03" };
	// string levels[LEVELS] = { "cambioLvl", "cambioLvl", "cambioLvl" }; // -> Para llegar a la pantalla de victoria
	int currentLevel;
	
	// Vidas
	int life;

public:
	// Constructora (vacía y a partir de archivo) y destructora
	Game();
	~Game();

	// Métodos esenciales
	void run();
	void handleEvents();
	void render();
	void update();

	// Collides
	bool collidesBall(SDL_Rect rectBall, Vector2D& v);
	bool collidesReward(SDL_Rect rectBall, char type, Reward* rew);

	//Comportamiento de las Rewards
	void createReward(Vector2D rPos);
	void rewardBehaviour(char type);

	// Comprobaciones y vidas
	void checkNextLevel(bool rewardAct);
	void checkLife();
	void lifeLeft();
	void reloadItems();

	// Lectura y escritura de archivos
	void loadFromFile(string filename);
	void saveToFile(string filename);
	void userSaving();
};

