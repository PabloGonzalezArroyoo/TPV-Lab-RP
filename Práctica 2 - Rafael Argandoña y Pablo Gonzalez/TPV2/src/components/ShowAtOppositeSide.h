#pragma once
#include "Transform.h"
#include "../ecs/Manager.h"

struct ShowAtOppositeSide : public Component {
private:
	Transform* tr;
public:
	constexpr static cmpId_type id = _SHOWATOPPOSITESIDE;
	inline virtual void initComponent() { tr = mngr->getComponent<Transform>(ent); }
};