#pragma once
#include "Game.h"
#include "Menu.h"

class MainMenuState : public GameState
{
private:
	static void newGame(Game* g);
	static void loadGame(Game* g);
	static void quit(Game* g);
	
public:
	MainMenuState();
	MainMenuState(Game* g);
	virtual ~MainMenuState() {};
};

