#pragma once

#include "Transform.h"
class Game;
class FighterCtrl : public Component {
private:
	Game* game;
	Transform* tr;
	float thrust;
	int r;
	float speedLimit;

public:
	constexpr static cmpId_type id = _FIGHTERCTRL;

	// Constructora
	FighterCtrl(Game* g): Component(), game(g), tr(nullptr), thrust(0.2), r(0), speedLimit(1.5) {}
	
	// Metodos virtuales
	virtual void initComponent();
	virtual void update();

	// Input
	void handleInput();

	//Setter
	void setRot(int _rot) { r = _rot; }
};