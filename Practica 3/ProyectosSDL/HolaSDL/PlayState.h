#pragma once
#include "GameState.h"

using namespace std;
typedef unsigned int uint;

// Constantes
const uint WIN_WIDTH = 800;
const uint WIN_HEIGTH = 600;
const uint NUM_LEVELS = 3;
const uint NUM_LIFES = 3;

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

	// Iteradores
	list<GameObject*>::iterator itBall;
	vector< list<GameObject*>::iterator> objToDestroy;

public:
	PlayState();
	PlayState(Game* g);
	virtual ~PlayState();

	// Métodos esenciales
	virtual void update();
	virtual void render();
	virtual void handleEvent();

	// Collides
	bool collidesBall(SDL_Rect rectBall, Vector2D& v);
	bool collidesReward(SDL_Rect rectBall);

	//Comportamiento de las Rewards
	void createReward(Vector2D rPos);
	void rewardBehaviour(char type);
	void deleteReward(Reward* reward);

	// Comprobaciones y vidas
	void checkNextLevel(bool rewardAct);
	void checkLife();
	void lifeLeft();
	void reloadItems();
};

