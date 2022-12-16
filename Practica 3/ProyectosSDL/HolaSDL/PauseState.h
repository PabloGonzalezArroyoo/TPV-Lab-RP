#pragma once
#include "GameState.h"

class PauseState : public GameState
{
private:
	// Funciones para los botones
	static void resume(Game* g);
	static void saveGame(Game* g);
	static void mainMenu(Game* g);

public:
	// Constructoras y destructora
	PauseState() : GameState() {};
	PauseState(Game* g);
	virtual ~PauseState() {};
};

