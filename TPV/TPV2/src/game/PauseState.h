#pragma once
#include "GameState.h"

class PauseState : public GameState {
private:

public:
	PauseState(Game* g, int plLifes);

	virtual void update();
};