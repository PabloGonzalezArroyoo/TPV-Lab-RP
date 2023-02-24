#pragma once

#include "Transform.h"

class ShowAtOppositeSide : public Component {
private:
	Transform* tr;

public:
	static const int id = _SHOWATOPPOSITESIDE;

	ShowAtOppositeSide() : Component(), tr(nullptr) { }

	virtual void initComponent();
	virtual void update();
};