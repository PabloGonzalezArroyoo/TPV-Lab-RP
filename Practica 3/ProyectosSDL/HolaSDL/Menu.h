#pragma once
#include "GameObject.h"
#include "MenuButton.h"
#include "Constantes.h"
#include <list>

class Menu : public GameObject
{
private:
	Texture* texture;

public:
	// Constructora y destructora
	Menu(Texture* _texture);
	virtual ~Menu() {};

	virtual void render();
};

