#pragma once
#include "../ecs/Manager.h"

class GameState {
protected:
	// list<GameObject*> objects;
	// Game* game;

public:
	// Métodos esenciales
	virtual void update();
	virtual void render();
	virtual void handleEvent();
};