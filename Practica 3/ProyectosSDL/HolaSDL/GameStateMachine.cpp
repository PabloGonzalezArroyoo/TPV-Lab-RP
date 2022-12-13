#include "GameStateMachine.h"

// Destructora - Borrar estados hasta que la pila est� vac�a
GameStateMachine::~GameStateMachine() {
	while (!states.empty()) states.pop();
}

// A�adir un nuevo estado a la pila
void GameStateMachine::pushState(GameState* state) {
	states.push(state);
}

// Elimina el estado de la pila
void GameStateMachine::popState() {
	states.pop();
}

// Borra todos los estados acumulados en la pila
void GameStateMachine::discardStates() {
	while (!states.empty()) popState();
}

// Cambia estados de forma que borra el anterior y a�ade uno nuevo
void GameStateMachine::changeState(GameState* state) {
	popState();
	pushState(state);
}

