#pragma once

#include "Transform.h"

class FighterCtrl : public Component {
private:
	Transform* tr;
public:
	static const int id = _FIGHTERCTRL;

	// Constructora
	FighterCtrl(): Component(), tr(nullptr) { }
	
	// Metodos virtuales
	virtual void initComponent();
	virtual void update();

	// Input
	void handleInput();
};