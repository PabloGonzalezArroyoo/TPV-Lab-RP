#pragma once

#include "Transform.h"

class ShowAtOppositeSide : public Component {
private:
	Transform* tr;

public:
	ShowAtOppositeSide() : Component(), tr(nullptr) { }
	
	virtual void initComponent();
	virtual void update();
}