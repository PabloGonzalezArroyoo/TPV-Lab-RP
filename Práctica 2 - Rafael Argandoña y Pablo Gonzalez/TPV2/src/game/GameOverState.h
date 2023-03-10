#pragma once
#include "GameState.h"

class GameOverState : public GameState {
private:

public:
	// Constructora
	GameOverState(Game* g);

	// Sobrecarga del método update
	virtual void update();
};