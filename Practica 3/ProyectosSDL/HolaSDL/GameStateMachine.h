#pragma once
#include <stack>
#include "GameState.h"

class GameStateMachine
{
private:
	stack<GameState*> states;
	GameState* currentState;

public:
	GameState* currentState() { return states.top(); };
	void pushState(GameState* _state);
	void changeState(GameState* newState);
	void popState();
};

