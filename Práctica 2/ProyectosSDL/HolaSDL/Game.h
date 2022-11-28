// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Paddle.h"
#include "Ball.h"
#include "BlocksMap.h"
#include "Wall.h"
#include "Reward.h"
#include "checkML.h"
#include <iostream>
#include <fstream>
#include <list>

using namespace std;
typedef unsigned int uint;

// Constantes
const uint winWidth = 800;
const uint winHeight = 600;
const uint frameRate = 5;
const uint wallWidth = 15;
const uint nTextures = 9;
const uint nLevels = 3;
const uint numLifes = 1;

// Enum con el nº de la textura correspondiente dentro del array
enum TextureName {BallTxt, Blocks, Digits, GameOver, PaddleTxt, SideWall, TopWall, Winner, Rewards};

// Struct con el nombre y las dimensiones de frames del archivo
typedef struct {
	string filename;
	uint hframes, vframes;
} TextureDescription;

// Descripción de las texturas (según la estructura del struct anterior)
const TextureDescription textDescription[nTextures] = {
	{"../images/ball2.png", 1, 1},
	{"../images/bricks2.png", 2, 3},
	{"../images/digits2.png", 3, 4},
	{"../images/gameover1.png", 1, 1},
	{"../images/paddle2.png", 1, 1},
	{"../images/side.png", 1, 1},
	{"../images/topside.png", 1, 1},
	{"../images/youwin.png", 1, 1},
	{"../images/rewards.png", 10, 8}
};

class Game {
private:
	// virtual list<ArkanoidObject> gameObjects;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit, gameOver, win;

	Paddle* paddle = nullptr;
	Ball* ball = nullptr;
	BlocksMap* blockmap = nullptr;
	Wall* walls[3];
	string levels[nLevels] = { "level01", "level02", "level03" };
	// { "cambioLvl", "cambioLvl", "cambioLvl" }; // -> Para llegar a la pantalla de victoria
	Reward* reward = nullptr;
	list<ArkanoidObject*> objects;
	
	Texture* textures[nTextures];

	int life = numLifes;
	int currentLevel;

	list<ArkanoidObject*>::iterator itBlocksMap;

public:
	// Constructora (vacía y a partir de archivo) y destructora
	Game();
	Game(string player);
	~Game();

	// Métodos esenciales
	void run();
	void handleEvents();
	void render();
	void update();

	// Collides
	bool collidesBall(SDL_Rect rectBall, Vector2D& v);
	bool collidesReward(SDL_Rect rectBall, char type);

	//Reward behaviour
	void createReward(Vector2D rPos);
	void rewardBehaviour(char type);

	// Comprobaciones y vidas
	void checkNextLevel(bool rewardAct);
	void checkLife();
	void lifeLeft();

	// Lectura y escritura de archivos
	void loadFromFile(string filename);
	void saveToFile(string filename);
	void userSaving();
};

