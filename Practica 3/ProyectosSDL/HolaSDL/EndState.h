// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once
#include "GameState.h"

// CLASE ENDSTATE - ESCENA DEL JUEGO (GAMESTATE):
// Propiedades
//		- Hereda las de GameState (image, game)
// Metodos:
//		Constructora	-> Sobrecargada con el puntero al Juego y un booleano de informacion sobre si el jugador ha ganado o perdido
//		Destructora		-> Se ejecuta la destructora del padre (GameState)
//	M�todos utilizado por los botones (introducidos mediante callbacks):
//		newGame			-> Metodo que accede a la maquina de estados del juego para volver a cargar una nueva escena de juego
//		mainMenu		-> Vuelve al estado del men�
//		quit			-> Cierra el juego

class PlayState;
class EndState : public GameState
{
private:
	static void newGame(Game* g);
	static void mainMenu(Game* g);
	static void quit(Game* g);

public:
	EndState(Game* g, bool win);
	virtual ~EndState() {};
};

