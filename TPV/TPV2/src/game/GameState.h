#pragma once
#include "../ecs/Manager.h"

class GameState {
protected:
	// list<GameObject*> objects;
	// Game* game;

public:
	// M�todos esenciales
	virtual void update();
	virtual void render();
	virtual void handleEvent();
};