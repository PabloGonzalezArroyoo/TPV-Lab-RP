#pragma once
#include "ArkanoidObject.h"

class Menu : public ArkanoidObject
{
private:
	bool exit = false;
	char type;
	Vector2D click;
	SDL_Rect play;
	SDL_Rect load;

public:
	// Constructora y destructora
	Menu(Vector2D _pos, uint _w, uint _h, Texture* _texture);
	virtual ~Menu();

	// Métodos esenciales
	void run();
	virtual void handleEvent();

	// Porcesar input
	char setClick(double x, double y);
	char getType() { return type; };
};

