#pragma once
#include <list>
#include "GameObject.h"
#include "Game.h"

// Enum con el nº de la textura correspondiente dentro del array
enum TextureName { BallTxt, Blocks, Digits, GameOver, PaddleTxt, SideWall, TopWall, Winner, Rewards, MainMenu };

class GameState
{
// Protected -> Accesible desde esta clase y sus herederas
protected:
	list<GameObject*> objects;
	Game* game;

public :
	GameState() { game = nullptr; };
	GameState(Game* g) { game = g; };
	virtual ~GameState() { };

	virtual void update();
	virtual void render();
	virtual void handleEvent(SDL_Event e);
};

