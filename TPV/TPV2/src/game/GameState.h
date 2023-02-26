#pragma once
#include "../ecs/Manager.h"
#include <list>
class Game;
class GameState {
protected:
	Manager* mng;
	Game* game;

public:
	GameState() : game(nullptr) { }
	GameState(Game* g) : game(g) { }
	// Métodos esenciales
	virtual void update();
	virtual void render();
	virtual void handleEvent();
	virtual void run();

	virtual void newState();
};