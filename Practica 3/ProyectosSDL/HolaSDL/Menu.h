#pragma once
#include "GameObject.h"
#include "MenuButton.h"
#include <list>

class Menu : public GameObject
{
private:
	bool exit = false;
	char type; // { P = Pause, F = Final, M = Main menu }

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

