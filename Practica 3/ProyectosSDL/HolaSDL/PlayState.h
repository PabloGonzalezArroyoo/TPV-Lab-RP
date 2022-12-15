#pragma once
#include "GameState.h"
#include <vector>
#include <list>

using namespace std;
typedef unsigned int uint;

class game;
class PlayState : public GameState
{
private:
	// Variables de flujo
	bool gameOver, win, isPaused;

	// Niveles
	string levels[NUM_LEVELS] = { "level01", "level02", "level03" };
	//string levels[NUM_LEVELS] = { "cambioLvl", "level02", "cambioLvl" }; // -> Para llegar a la pantalla de victoria

	// Vidas y nivel actual
	int life, currentLevel;

	// Punteros a objetos (acceso directo)
	BlocksMap* blocksmap;
	Paddle* paddle;
	Wall* walls[3];
	Ball* ball;

	// Iteradores
	list<GameObject*>::iterator itFirstReward;
	vector<list<GameObject*>::iterator> objToDestroy;

public:
	// Constructoras y destructora
	PlayState();
	PlayState(Game* g);
	virtual ~PlayState();

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

	// Comprobaciones y vidas
	void checkNextLevel(bool rewardAct);
	void checkLife();
	void lifeLeft();
	void reloadItems();
	void userSaving();
};

