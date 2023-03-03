#pragma once
#include "GameState.h"
#include "AsteroidsController.h"

class PlayState : public GameState {
private:
	// Refrencia a mi controlador de asteroides
	AsteroidsController* astController;
	// 
	bool gameOver;
public:
	// Constructora y destructora
	PlayState(Game* g);
	virtual ~PlayState();

	//Sobrecarga del metodo update
	virtual void update();

	// Comprobacion de colisiones
	void checkCollisions();

	// M�todos de reacci�n ante eventos sobre el jugador
	void OnPlayerDamage(Entity* pl);
	void OnPlayerDies();
};