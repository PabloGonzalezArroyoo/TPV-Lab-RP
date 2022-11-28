#pragma once
#include "ArkanoidObject.h"

typedef unsigned int uint;
const uint winW = 800;
const uint winH = 600;

class Menu : public ArkanoidObject
{
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;
	char type;
	Vector2D click;
	SDL_Rect play;
	SDL_Rect load;

public:
	// Constructora y destructora
	Menu();
	~Menu();

	// Métodos esenciales
	void run();
	virtual void handleEvent();

	// Porcesar input
	char setClick(double x, double y);
	char getType() { return type; };
};

