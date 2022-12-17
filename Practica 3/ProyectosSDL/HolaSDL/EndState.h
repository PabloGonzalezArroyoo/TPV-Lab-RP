// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
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

