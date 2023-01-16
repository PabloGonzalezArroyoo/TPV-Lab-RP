// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once
#include "GameState.h"

// CLASE MAINMENUSTATE - ESCENA DEL JUEGO (GAMESTATE):
// Propiedades
//		- Hereda las de GameState (image, game)
// Metodos:
//		Constructora	-> Sobrecargada con el puntero al Juego y un booleano de informacion sobre si el jugador ha ganado o perdido
//		Destructora		-> Se ejecuta la destructora del padre (GameState)
//	Métodos utilizado por los botones (introducidos mediante callbacks):
//		newGame			-> Metodo que accede a la maquina de estados del juego para cargar una nueva escena de juego
//		loadGame		-> Carga una escena nueva de juego con unos parámetros obtenidos al leer un archivo
//		quit			-> Cierra el juego

class MainMenuState : public GameState
{
private:
	// Funciones para los botones
	static void newGame(Game* g);
	static void loadGame(Game* g);
	static void quit(Game* g);
	
public:
	// Constructora y destructora
	MainMenuState(Game* g);
	virtual ~MainMenuState() {};
};