#pragma once
#include "GameObject.h"
#include "Game.h"
typedef void Callback (Game* game);

const int WIDTH = 200, HEIGHT = 50;

enum ButtonState { OnOut, OnOver, OnClick };

class MenuButton : public GameObject
{
private:
	Vector2D pos;
	Texture* texture;
	int state;
	//CallBack* funct;
	Callback* myC;
public:
	MenuButton();
	MenuButton(Vector2D _pos, Texture* _txt, void (*callback)(Game* g));
	
	virtual void render();
	virtual void handleEvent(SDL_Event e);
	virtual void update();
};

