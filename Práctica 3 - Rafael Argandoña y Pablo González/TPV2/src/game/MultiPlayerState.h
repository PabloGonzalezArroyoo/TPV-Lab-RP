#pragma once
#include "GameState.h"

class MultiPlayerState : public GameState {
private:

public:
	MultiPlayerState();

	// Sobrecarga del m�todo update
	virtual void update();
};