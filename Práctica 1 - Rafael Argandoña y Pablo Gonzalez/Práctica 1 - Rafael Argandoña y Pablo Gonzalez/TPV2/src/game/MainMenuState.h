#pragma once
#include "GameState.h"

class MainMenuState : public GameState {
private:

public:
	// Constructora
	MainMenuState(Game* g);

	// Sobrecarga del m�todo update
	virtual void update();
};