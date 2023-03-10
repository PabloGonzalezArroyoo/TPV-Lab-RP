#pragma once

#include "Transform.h"

class DeAcceleration : public Component {
private:
	// Referencia a mi transform
	Transform* tr;

public:
	// Id del componente
	constexpr static cmpId_type id = _DEACCELERATION;

	// M�todos virtuales
	virtual void initComponent();

	// Decelera la nave en cada iteraci�n bajando la velocidad un 0.005%
	virtual void update();
};