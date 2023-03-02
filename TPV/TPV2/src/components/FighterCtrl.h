#pragma once
#include "../sdlutils/SoundEffect.h"
#include "Transform.h"
class Game;
class FighterCtrl : public Component {
private:
	Game* game;
	Transform* tr;
	float thrust;
	int r;
	float speedLimit;
	float startTime;
	float lastShotTime;
	SoundEffect* sound;

public:
	constexpr static cmpId_type id = _FIGHTERCTRL;

	// Constructora
	FighterCtrl(Game* g, SoundEffect* _sound): Component(), game(g), tr(nullptr), 
		thrust(0.2), r(0), speedLimit(1.5), sound(_sound) {}
	
	// Metodos virtuales
	virtual void initComponent();
	virtual void update();

	// Input
	void handleInput();

	//Setter
	void setRot(int _rot) { r = _rot; }
};