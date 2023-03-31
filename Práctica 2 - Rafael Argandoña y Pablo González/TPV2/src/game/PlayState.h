#pragma once
#include "GameState.h"

class PlayState : public GameState {
private:

public:
	// Constructora y destructora
	PlayState(Game* g);

	virtual void update();
};