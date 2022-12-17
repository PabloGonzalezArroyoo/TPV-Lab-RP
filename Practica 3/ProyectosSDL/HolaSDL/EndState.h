// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once
#include "GameState.h"

class PlayState;
class EndState : public GameState
{
private:
	static void newGame(Game* g);
	static void mainMenu(Game* g);
	static void quit(Game* g);

public:
	EndState();
	EndState(Game* g, bool win);
	virtual ~EndState() {};
};

