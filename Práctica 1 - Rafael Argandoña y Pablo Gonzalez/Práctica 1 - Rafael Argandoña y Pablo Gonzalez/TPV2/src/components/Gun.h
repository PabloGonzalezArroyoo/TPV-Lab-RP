#pragma once

#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class Game;
class Gun : public Component {
private:
	// Referencia a Game, a mi transform y a mi sonido a reproducir
	Game* game;
	Transform* tr;
	SoundEffect* sound;
	// Variables para el cooldown de disparo
	float startTime;
	float lastShotTime;

public:
	// Id del componente
	constexpr static cmpId_type id = _GUN;

	// Constructora
	Gun(Game* g, SoundEffect* _sound) : Component(), tr(nullptr), game(g),
		startTime(sdlutils().currRealTime()), lastShotTime(0), sound(_sound) { }

	// M�todos virtuales
	virtual void initComponent();
	virtual void update();
	
	// Input - disparo
	void handleInput();

	//Calculos para las balas
	Vector2D bulletPos();
	Vector2D bulletVel();
};