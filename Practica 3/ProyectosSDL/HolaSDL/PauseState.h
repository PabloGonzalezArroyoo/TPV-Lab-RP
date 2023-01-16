// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once
#include "GameState.h"

// CLASE PAUSESTATE - ESCENA DEL JUEGO (GAMESTATE):
// Propiedades
//		- Hereda las de GameState (image, game)
// Metodos:
//		Constructora	-> Sobrecargada con el puntero al Juego y un booleano de informacion sobre si el jugador ha ganado o perdido
//		Destructora		-> Se ejecuta la destructora del padre (GameState)
//	M�todos utilizado por los botones (introducidos mediante callbacks):
//		resume			-> Metodo que accede a la maquina de estados del juego para volver a la escena del juego
//		saveGame		-> Guarda la informacion del estado actual de la partida en un archivo
//		mainMenu		-> Vuelve al estado del men�

class PauseState : public GameState
{
private:
	// Funciones para los botones
	static void resume(Game* g);
	static void saveGame(Game* g);
	static void mainMenu(Game* g);

public:
	// Constructora y destructora
	PauseState(Game* g);
	virtual ~PauseState() {};
};

