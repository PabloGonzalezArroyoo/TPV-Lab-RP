#pragma once
#include "GameState.h"

class PauseState : public GameState
{
private:
	static void resume(Game* g);
	static void save(Game* g);
	static void mainMenu(Game* g);

public:
	PauseState();
	PauseState(Game* g);
	virtual ~PauseState() {};
};

