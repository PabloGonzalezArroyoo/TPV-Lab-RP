// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once
#include "GameState.h"
#include <vector>
#include <list>

using namespace std;
typedef unsigned int uint;

// CLASE PLAYSTATE - ESCENA DEL JUEGO (GAMESTATE):
// Propiedades
//		- Hereda las de GameState (image, game)
//		- gameOver, win, isPaused: variables de control de flujo que informan del estado del juego
//		- levels: array del tamaño de NUM_LEVELS con el nombre de cada archivo de cada nivel
//		- life: numero de vidas del jugador
//		- currentLevel: nivel actual en el que se encuentra el jugador
//		- blocksMap : puntero a mi mapa de bloques
//		- paddle: puntero a mi pala
//		- walls[]: array de punteros a mis paredes
//		- ball: puntero a mi pelota
//		- lifes: contenedor (pila) que almacena la ui de las vidas
//		- itFirstReward: iterador que apunta a la primera reward si existe, de lo contrario es nulo
//		- objectsToDestoy: vector de iteradores a la lista de objetos usado para prevenir borrar elementos antes de terminar los updates
// Metodos:
//		Constructora	-> Vacía y sobrecargada tanto con el puntero al juego (newGame) como con este y el archivo de lectura (load)
//		Destructora		-> Se ejecuta la destructora del padre (GameState)
//		update			-> si el juego no está pausado, se llama a los updates de todos los objetos (punteros y recorrido), se destruyen los
//						objetos a destruir y se comprueba si se ha completado el nivel
//		render			-> llama al render de todos los objetos
//		handleEvent		-> comprueba si se activa la pausa, de lo contrario se llama al handleEvent de la pala
//		collidesBall	-> llama a los collides de la bola con cada objeto del juego según proceda
//		collidesReward	-> llama al collides de la reward si esta se encuentra en el área de la pala
//		createReward	-> crea una reward en la posicion del último bloque destruido a partir de un valor aleatorio y actualiza el iterador si procede
//		rewardBehaviour -> realiza el efecto de la reward segun su tipo
//		deleteReward	-> añade la reward recibida como parametro como un objeto a destruir y si es la primera aumenta el iterador a la primera
//		checkNextLevel	-> comprueba si el jugador ha acabdo el juego (ha superado el ultimo nivel) y si no carga el siguiente nivel
//		addLife			-> aumenta el contador de vidas y añade una imagen de la UI de vidas
//		removeLife		-> decrece el contador de vidas del jugador y elimina una imagen de la UI de vidas
//		reloadItems		-> Devuelve la lista de objetos al estado inicial ("recarga" la escena)
//		saveToFile		-> Recorre la lista de objetos informando que deben guardar su informacion en el archivo abierto recibido como parametro

class game;
class PlayState : public GameState
{
private:
	// Variables de flujo
	bool gameOver, win, isPaused;

	// Niveles
	string levels[NUM_LEVELS] = { "level01", "level02", "level03" };
	//string levels[NUM_LEVELS] = { "cambioLvl", "cambioLvl", "cambioLvl" }; // -> Para llegar a la pantalla de victoria

	// Vidas y nivel actual
	int life, currentLevel;

	// Punteros a objetos (acceso directo)
	BlocksMap* blocksmap;
	Paddle* paddle;
	Wall* walls[3];
	Ball* ball;

	//Pila de iteradores apuntando a las vidas del jugador
	stack<list<GameObject*>::iterator> lifes;

	// Iteradores
	list<GameObject*>::iterator itFirstReward;
	vector<list<GameObject*>::iterator> objToDestroy;

public:
	// Constructoras y destructora
	PlayState();
	PlayState(Game* g);
	PlayState(Game* g, ifstream& in);
	virtual ~PlayState() {};

	// Métodos esenciales
	virtual void update();
	virtual void render();
	virtual void handleEvent(SDL_Event event);

	// Collides
	bool collidesBall(SDL_Rect rectBall, Vector2D& v);
	bool collidesReward(SDL_Rect rectBall);

	//Comportamiento de las Rewards
	void createReward(Vector2D rPos);
	void rewardBehaviour(char type);
	void deleteReward(list<GameObject*>::iterator reward);

	// Comprobaciones de nivel y vidas
	void checkNextLevel(bool rewardAct);
	
	// Vidas
	void addLife();
	void removeLife();

	// Guardado y reposicionamiento de items
	void reloadItems();
	void saveToFile(ofstream& out);
};

