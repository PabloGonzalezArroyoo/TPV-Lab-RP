#pragma once
#include "GameState.h"

class PauseState : public GameState {
private:

public:
	// Constructora
	PauseState(Game* g, int plLifes);

	// Sobrecarga del metodo update
	virtual void update();
};