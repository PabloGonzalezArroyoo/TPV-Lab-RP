#pragma once
#include "GameState.h"

class GameOverState : public GameState {
private:

public:
	// Constructora
	GameOverState(Game* g);

	// Sobrecarga del m�todo update
	virtual void update();
};