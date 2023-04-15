#pragma once
#include "GameState.h"

class WinState : public GameState{
private:

public:
	// Constructora
	WinState(Game* g);

	// Sobrecarga del método update
	virtual void update();
};