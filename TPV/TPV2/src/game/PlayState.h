#pragma once
#include "GameState.h"

class PlayState : public GameState {
private:
	bool paused, gameOver;
public:
	PlayState(Game* g);
};