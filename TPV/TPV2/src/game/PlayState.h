#pragma once
#include "GameState.h"
#include "AsteroidsController.h"

class PlayState : public GameState {
private:
	AsteroidsController* astController;
	bool gameOver;
public:
	PlayState(Game* g);
	virtual ~PlayState();

	virtual void update();

	void checkCollisions();

	void OnPlayerDamage(Entity* pl);
	void OnPlayerDies();
};