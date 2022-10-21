#pragma once
#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "Helicopter.h"
#include "Dog.h"

const int winWidth = 800;
const int winHeight = 600;
const int numTexture = 3;

class Game
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	Dog* dog = nullptr;
	Helicopter* helicopter = nullptr;
	bool exit = false;
	Texture* textures[numTexture];

public:
	Game();
	~Game();					// Destructor

	void run();
	void render() const;
	void handleEvents();
	void update();
};

