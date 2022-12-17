// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once
#include <stack>
#include "GameState.h"

class GameState;
class GameStateMachine
{
private:
	stack<GameState*> states;

public:
	// Constructoras y destructora
	GameStateMachine() {};
	GameStateMachine(GameState* firstState);
	~GameStateMachine();

	// M�todos de gesti�n de estados
	GameState* currentState() { return states.top(); };
	void pushState(GameState* _state);
	void changeState(GameState* newState);
	void popState();
	void discardStates();
};

