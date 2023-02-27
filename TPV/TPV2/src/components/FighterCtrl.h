#pragma once

#include "Transform.h"

class FighterCtrl : public Component {
private:
	Transform* tr;
	float thrust;
	int r;
	float speedLimit;

public:
	constexpr static cmpId_type id = _FIGHTERCTRL;

	// Constructora
	FighterCtrl(): Component(), tr(nullptr), thrust(0.2), r(0), speedLimit(2) {}
	
	// Metodos virtuales
	virtual void initComponent();
	virtual void update();

	// Input
	void handleInput();
};