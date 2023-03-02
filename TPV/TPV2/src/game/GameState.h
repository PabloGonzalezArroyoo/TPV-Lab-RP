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
#include "../utils/Collisions.h"
#include <list>

enum TEXTURE_NAME {
	FIGTHER, ASTEROIDS_GOLD, ASTEROIDS_SILVER, FIRE, HEALTH,
	MM_MESSAGE, PAUSE_MESSAGE, GO_MESSAGE,
};

enum SOUND_NAME {
	DOOM, EXPLOSION, FIRESFX, OOF, SELECT, TRHUST
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