#pragma once
#include "GameState.h"

class EndState : public GameState
{
private:

public:
	EndState();
	EndState(Game* g, bool win);
	virtual ~EndState() {};
};

