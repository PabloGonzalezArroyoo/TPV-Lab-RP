#pragma once
#include "GameState.h"
#include "AsteroidsController.h"

class PlayState : public GameState {
private:
	bool paused, gameOver;
	AsteroidsController* astController;
public:
	PlayState(Game* g);
	virtual ~PlayState();

	virtual void update();
};