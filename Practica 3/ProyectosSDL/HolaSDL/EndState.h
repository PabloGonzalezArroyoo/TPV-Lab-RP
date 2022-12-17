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

