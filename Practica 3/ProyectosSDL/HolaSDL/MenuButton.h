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
	//CallBack* funct;
public:
	Callback* myC;
	MenuButton();
	MenuButton(Vector2D _pos, Texture* _txt, Callback* _c );
	
	virtual void render();
	virtual void handleEvent(SDL_Event e);
	virtual void update();

	int getState() { return state; }
};

