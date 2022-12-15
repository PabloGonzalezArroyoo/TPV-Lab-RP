#pragma once
#include "GameState.h"

class MainMenuState : public GameState
{
private:
	// Funciones para los botones
	static void newGame(Game* g);
	static void loadGame(Game* g);
	static void quit(Game* g);
	
public:
	// Constructoras y destructora
	MainMenuState() : GameState() {};
	MainMenuState(Game* g);
	virtual ~MainMenuState() {};
	
	// M�todos esenciales
	virtual void handleEvent(SDL_Event e);
};