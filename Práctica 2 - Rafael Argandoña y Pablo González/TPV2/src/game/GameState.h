#pragma once
#include "../ecs/Manager.h"

#include "../systems/GameCtrlSystem.h"
#include "../systems/AsteroidsSystem.h"
#include "../systems/BulletSystem.h"
#include "../systems/FighterSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/SoundSystem.h"

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

	virtual ~GameState() { }

	// Métodos esenciales
	virtual void update() { mng->update(); }
	virtual void render() { }
	virtual void refresh() { mng->refresh(); }
};