#pragma once

#include "Transform.h"

class Gun : public Component {
private:
	Transform* tr;

public:
	// Constructora
	Gun() : Component(), tr(nullptr) { }

	// M�todos virtuales
	virtual void initComponent();
	virtual void update();
	
	// Input - disparo
	void handleInput();
};