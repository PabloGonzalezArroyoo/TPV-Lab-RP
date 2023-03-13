#pragma once
#include "Transform.h"
#include "../ecs/Manager.h"

struct DeAccelerationComponent : public Component {
protected:
	Transform* tr;

public:
	// ID
	constexpr static cmpId_type id = _DEACCELERATION;

	// Inicializar componente
	inline virtual void initComponent() { tr = mngr->getComponent<Transform>(ent); }
};