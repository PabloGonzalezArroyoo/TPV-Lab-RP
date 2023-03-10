#pragma once

#include "Transform.h"

class ShowAtOppositeSide : public Component {
private:
	// Referencia a mi transform
	Transform* tr;

public:
	// Id del componente
	constexpr static cmpId_type id = _SHOWATOPPOSITESIDE;

	// Constructora
	ShowAtOppositeSide() : Component(), tr(nullptr) { }

	// Métodos virtuales
	virtual void initComponent();
	virtual void update();
};