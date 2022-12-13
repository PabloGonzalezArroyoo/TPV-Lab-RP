#pragma once
#include <stack>
#include "GameState.h"

class GameStateMachine
{
private:
	stack<GameState*> states;

public:
	GameStateMachine();
	~GameStateMachine();
	GameState* currentState() { return states.top(); };
	
	void pushState(GameState* _state);
	void changeState(GameState* newState);
	void popState();
	void discardStates();
};

