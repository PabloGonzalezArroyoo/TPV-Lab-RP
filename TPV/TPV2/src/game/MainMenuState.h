#pragma once
#include "GameState.h"

class MainMenuState : public GameState {
private:

public:
	MainMenuState(Game* g);

	virtual void update();
};