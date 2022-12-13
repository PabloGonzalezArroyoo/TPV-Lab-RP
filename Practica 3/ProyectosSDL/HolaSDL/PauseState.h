#pragma once
#include "Game.h"

class PauseState : public GameState
{
public:
	PauseState();
	PauseState(Game* g);
	~PauseState();
};

