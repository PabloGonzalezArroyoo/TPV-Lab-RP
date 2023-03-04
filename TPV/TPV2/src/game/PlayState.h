#pragma once
#include "GameState.h"
#include "AsteroidsController.h"

class PlayState : public GameState {
private:
	// Refrencia a mi controlador de asteroides
	AsteroidsController* astController;

public:
	// Constructora y destructora
	PlayState(Game* g);
	virtual ~PlayState();

	//Sobrecarga del metodo update
	virtual void update();

	// Comprobacion de colisiones
	void checkCollisions();
	bool collisionAsteroidPlayer();
	void collisionAsteroidBullet();

	// M�todos de reacci�n ante eventos sobre el jugador
	void OnPlayerDamage(Entity* pl);
	void OnPlayerDies();
};