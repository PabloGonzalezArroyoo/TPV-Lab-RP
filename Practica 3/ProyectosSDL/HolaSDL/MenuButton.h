#pragma once
#include "GameObject.h"
#include "Game.h"
typedef void CallBack(Game* game);

class MenuButton : public GameObject
{
private:
	Vector2D pos;
	Texture* texture;
	CallBack* func;
	bool onRelease;
	
public:
	MenuButton(Game(*callBack)) {
		func (callBack);
	}
	
	virtual void render();
	virtual void handleEvent(SDL_Event e);
};

