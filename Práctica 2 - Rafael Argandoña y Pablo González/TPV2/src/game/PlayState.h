#pragma once
#include "GameState.h"

class PlayState : public GameState {
private:

public:
	// Constructora y destructora
	PlayState(Game* g);

	// Métodos de reacción ante eventos sobre el jugador
	void OnPlayerDamage(Entity* pl);
	void OnPlayerDies();
};