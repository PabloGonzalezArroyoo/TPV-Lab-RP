#pragma once
#include "GameState.h"

class MainMenuState : public GameState {
private:

public:
	// Constructora
	MainMenuState(Game* g);

	// Sobrecarga del método update
	virtual void update();
};