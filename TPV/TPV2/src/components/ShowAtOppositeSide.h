#pragma once

#include "Transform.h"

class ShowAtOppositeSide : public Component {
private:
	Transform* tr;

public:
	constexpr static cmpId_type id = _SHOWATOPPOSITESIDE;

	ShowAtOppositeSide() : Component(), tr(nullptr) { }

	virtual void initComponent();
	virtual void update();
};