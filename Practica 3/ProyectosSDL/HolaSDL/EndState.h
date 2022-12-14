#pragma once
#include "GameState.h"

class EndState : public GameState
{
private:
	static void newGame(Game* g);
	static void loadGame(Game* g);
	static void quit(Game* g);

public:
	EndState();
	EndState(Game* g, bool win);
	virtual ~EndState() {};
};

