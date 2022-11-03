#pragma once
#include "Texture.h"

class Dog
{
private:
	Texture* myTexture;
	SDL_Rect dest;
	int row, col;
	int mov = 50, anim = 100;
	int vx = 15, vy = 0;
	bool stop = false;

public:
	Dog(Texture* txt);
	~Dog();
	void render();
	void move(int winW, int winH);
	void handleEvents(SDL_Event event);
};
