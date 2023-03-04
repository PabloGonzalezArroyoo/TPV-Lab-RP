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

// Enumerado de las texturas
enum TEXTURE_NAME {
	FIGTHER, ASTEROIDS_GOLD, ASTEROIDS_SILVER, FIRE, HEALTH,
	MM_MESSAGE, PAUSE_MESSAGE, GO_MESSAGE,
};

// Enumerado de los sonidos
enum SOUND_NAME {
	EXPLOSION, FIRESFX, OOF, SELECT, THRUST
};

// Enumerado de los sonidos
enum MUSIC_NAME {
	GALAXY
};

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

	// M�todos esenciales
	virtual void update();
	virtual void render();
	virtual void refresh();
};