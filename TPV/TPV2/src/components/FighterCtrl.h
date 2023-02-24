#pragma once

#include "Transform.h"

class FighterCtrl : public Component {
private:
	Transform* tr;
public:
	// Constructora
	FighterCtrl(): Component(), tr(nullptr) { }
	
	// Metodos virtuales
	virtual void initComponent();
	virtual void update();

	// Input
	void handleInput();
};