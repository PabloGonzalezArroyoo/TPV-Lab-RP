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

// Para evitar la dependencia circular
class Game;
class GameState {
protected:
	// Referencia al manager que contengo y a Game
	Manager* mng;
	Game* game;

public:
	// Constructoras
	GameState() : game(nullptr), mng(nullptr) { }
	GameState(Game* g) : game(g), mng(nullptr) { }

	virtual ~GameState();

	// Métodos esenciales
	virtual void update();
	virtual void render();
	virtual void refresh();
};