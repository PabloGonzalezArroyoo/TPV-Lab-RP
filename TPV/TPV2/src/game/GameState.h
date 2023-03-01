#pragma once
#include "../ecs/Manager.h"
#include "../components/DeAcceleration.h"
#include "../components/DisableOnEXit.h"
#include "../components/FighterCtrl.h"
#include "../components/Follow.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../components/Gun.h"
#include "../components/Health.h"
#include "../components/Image.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Transform.h"
#include <list>

enum TEXTURE_NAME {
	FIGTHER, ASTEROIDS_GOLD, ASTEROIDS_SILVER, FIRE
};

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
	virtual void refresh();

	virtual void newState();
};