#include "GameStateMachine.h"

// Destructora - Borrar estados hasta que la pila esté vacía
GameStateMachine::~GameStateMachine() {
	while (!states.empty()) states.pop();
}

// Añadir un nuevo estado a la pila
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

// Cambia estados de forma que borra el anterior y añade uno nuevo
void GameStateMachine::changeState(GameState* state) {
	popState();
	pushState(state);
}

