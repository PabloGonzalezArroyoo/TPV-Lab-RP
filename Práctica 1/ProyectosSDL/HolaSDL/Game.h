#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Paddle.h"
#include "Ball.h"
#include "BlocksMap.h"
#include "Wall.h"
#include <iostream>

using namespace std;
typedef unsigned int uint;

// Constantes
const uint winWidth = 800;
const uint winHeight = 600;
const uint frameRate = 5;
const uint wallWidth = 15;
const uint nTextures = 8;

// Enum con el nº de la textura correspondiente dentro del array
enum TextureName {BallTxt, Blocks, Digits, GameOver, PaddleTxt, SideWall, TopWall, Winner};

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
	{"../images/youwin.png", 1, 1}
};

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit, gameOver, win;

	Paddle* paddle = nullptr;
	Ball* ball = nullptr;
	BlocksMap* blockmap = nullptr;
	Wall* walls[3];
	string levels[3];
	
	Texture* textures[nTextures];

	int currentLevel;

public:
	Game();
	~Game();

	void run();
	void handleEvents();
	void render();
	void update();
	bool collides(SDL_Rect rectBall, Vector2D& v);
	void checkNextLevel();
};

