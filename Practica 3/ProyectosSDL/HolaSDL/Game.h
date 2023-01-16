// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "GameStateMachine.h"
#include "Vector2D.h"
#include "checkML.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

#ifdef _WIN32
	#include<windows.h>
#endif

using namespace std;
typedef unsigned int uint;

// Struct con el nombre y las dimensiones de frames del archivo
typedef struct {
	string filename;
	uint hframes, vframes;
} TextureDescription;

// Descripción de las texturas (según la estructura del struct anterior)
const TextureDescription textDescription[NUM_TEXTURES] = {
	// Objetos
	{"ball2", 1, 1},
	{"bricks2", 2, 3},
	{"digits2", 3, 4},
	{"gameover", 1, 1},
	{"paddle2", 1, 1},
	{"side", 1, 1},
	{"topside", 1, 1},
	{"rewards", 10, 8},

	// Menús
	{"win", 1, 1},
	{"menu", 1, 1},
	{"pause", 1, 1},

	// Botones
	{"play", 1, 3},
	{"load", 1, 3},
	{"exit", 1, 3},
	{"resume", 1, 3},
	{"main", 1, 3},
	{"restart", 1, 3},
	{"save", 1, 3}
};

class PlayState;
class MainMenuState;
class PauseState;
class EndState;
class GameStateMachine;

//CLASE GAME - JUEGO:
// Propiedades:
//		- window y render: punteros para crear la ventana SDL
//		- exit: booleano de control para saber si el jugador ha salido del juego
//		- textures: array con las distintas texturas
//		- gsm: puntero a la máquina de estados
// Metodos:
//		Constructora	-> crea la aplicación de SDL, crea las textura y la máquina de estados para controlar las escenas del juego
//		Destructora		-> elimina las texturas, destruye la máquina de estados y cierra la aplicación de SDL
//		run				-> método que contiene el bucle de juego
//		render			-> limpia la pantalla, llama al método de renderizado de la escena actual y pinta en la pantalla
//		update			-> llama al update de la escena actual de la máquina de estados
//		handleEvents	-> si hay un evento, se pide que la escena actual del juego decida que hacer con él
//		getTexture		-> devuelve el puntero a la textura en base a un entero recibido
//		getStateMachine	-> devuelve el púntero de la gameStateMachine
//		changeControl	-> marca el cierre del juego
//		saveGame		-> pide el código del jugador (nombre del archivo), genera el archivo de guardado y llama a la función de guardar
//						estado de play

class Game {
private:
	// Punteros SDL
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	// Variables de flujo
	bool exit;
	
	// Texturas
	Texture* textures[NUM_TEXTURES];

	// Máquina de estados
	GameStateMachine* gsm;

public:
	// Constructora y destructora
	Game();
	~Game();

	// Métodos esenciales
	void run();
	void render();
	void update();
	void handleEvents();

	// Getters
	Texture* getTexture(int texture);
	GameStateMachine* getStateMachine() { return gsm; };
	void changeControl() { exit = true; };
	
	// Maquina de estados
	void saveGame();
};

