#pragma once
#include "GameState.h"

class WinState : public GameState{
private:

public:
	// Constructora
	WinState(Game* g);

	// Sobrecarga del m�todo update
	virtual void update();
};