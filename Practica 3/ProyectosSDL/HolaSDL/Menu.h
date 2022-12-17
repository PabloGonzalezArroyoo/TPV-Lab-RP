// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once
#include "GameObject.h"
#include <list>

class Menu : public GameObject
{
private:
	Texture* texture;

public:
	// Constructora y destructora
	Menu(Texture* _texture) { texture = _texture; };
	virtual ~Menu() {};

	// Métodos esenciales
	virtual void render() {
		SDL_Rect rect;
		rect.x = 0, rect.y = 0;
		rect.w = WIN_WIDTH, rect.h = WIN_HEIGHT;
		texture->render(rect);
	};
};

