// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once
#include "GameObject.h"

class Game;
typedef void Callback (Game* game);

enum ButtonState { OnOut, OnOver, OnClick };


class MenuButton : public GameObject
{
private:
	Vector2D pos;
	Texture* texture;
	int state;
	Callback* myC;
	Game* game;

public:
	// Constructora
	MenuButton();
	MenuButton(Vector2D _pos, Texture* _txt, Callback* _c, Game* g);
	
	// M�todos eneciales
	virtual void render();
	bool handleEvents(SDL_Event e);
	virtual void update();

	// Getter
	int getState() { return state; }
};

