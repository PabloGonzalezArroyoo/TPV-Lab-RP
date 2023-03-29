#pragma once
#include "GameState.h"

class PlayState : public GameState {
private:

public:
	// Constructora y destructora
	PlayState(Game* g);

	//Sobrecarga del metodo update
	virtual void update();

	// Comprobacion de colisiones
	void checkCollisions();
	bool collisionAsteroidPlayer(Entity* player, Transform* astTr);
	bool collisionAsteroidBullet(Transform* asteroid);

	// Métodos de reacción ante eventos sobre el jugador
	void OnPlayerDamage(Entity* pl);
	void OnPlayerDies();
};