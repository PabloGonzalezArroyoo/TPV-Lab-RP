// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once
#include <stack>
#include "GameState.h"

class GameState;

// CLASE GAMESTATEMACHINE - MAQUINA DE ESTADOS DE CONTROL DE ESCENAS:
// Propiedades
//		- states: pila con las distintas escenas (se procesar� la que est� en top())
// Metodos:
//		Constructora	-> Vac�a y sobrecargada con un puntero al primer estado del juego
//		Destructora		-> Elimina los estados de la pila
//		currentState	-> devuelve un puntero al top de la pila (=estado actual)
//		pushState		-> a�ade el estado recibido a la pila
//		changeState		-> reemplaza el estado actual por el nuevo estado
//		popState		-> borra el estado en el top() de la pila
//		discardStates	-> elimina todos los estados existentes en la pila 

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

