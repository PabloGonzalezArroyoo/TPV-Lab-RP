#pragma once

#include "Transform.h"

class Gun : public Component {
private:
	Transform* tr;

public:
	static const int id = _GUN;

	// Constructora
	Gun() : Component(), tr(nullptr) { }

	// Métodos virtuales
	virtual void initComponent();
	virtual void update();
	
	// Input - disparo
	void handleInput();
};