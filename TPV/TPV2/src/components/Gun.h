#pragma once

#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class Game;
class Gun : public Component {
private:
	Transform* tr;
	Game* game;
	float startTime;
	float lastShotTime;
public:
	constexpr static cmpId_type id = _GUN;

	// Constructora
	Gun(Game* g) : Component(), tr(nullptr), game(g), startTime(SDLUtils::instance()->currRealTime()), lastShotTime(0) { }

	// Métodos virtuales
	virtual void initComponent();
	virtual void update();
	
	// Input - disparo
	void handleInput();

	//Calculos para las balas
	Vector2D bulletPos();
	Vector2D bulletVel();
};