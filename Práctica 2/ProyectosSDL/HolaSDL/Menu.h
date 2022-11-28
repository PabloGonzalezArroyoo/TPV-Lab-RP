#pragma once
#include "ArkanoidObject.h"

const uint winWidth = 800;
const uint winHeight = 600;

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
	Menu(Texture* _texture);

	void run();
	virtual void handleEvent(SDL_MouseButtonEvent e) {};

	char setClick(double x, double y);
	char getType() { return type; };
};

