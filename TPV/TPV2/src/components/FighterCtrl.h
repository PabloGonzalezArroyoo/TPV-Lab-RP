#pragma once

#include "Transform.h"

class FighterCtrl : public Component {
private:
	Transform* tr;
public:
	constexpr static cmpId_type id = _FIGHTERCTRL;

	// Constructora
	FighterCtrl(): Component(), tr(nullptr) { }
	
	// Metodos virtuales
	virtual void initComponent();
	virtual void update();

	// Input
	void handleInput();
};