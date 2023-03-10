#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include "../ecs/Manager.h"

struct DeAccelerationComponent : public Component {
protected:
	Transform* tr;
public:
	constexpr static cmpId_type id = _DEACCELERATION;

	virtual void initComponent() { tr = mngr->getComponent<Transform>(ent); }
};