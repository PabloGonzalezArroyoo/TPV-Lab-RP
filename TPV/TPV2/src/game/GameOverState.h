#pragma once
#include "GameState.h"

class GameOverState : public GameState {
private:

public:
	GameOverState(Game* g);

	virtual void update();
};