#pragma once
#include "Transform.h"
#include "../ecs/Manager.h"

struct DisbaleOnExit : public Component {
private:
	Transform* tr;

public:
	constexpr static cmpId_type id = _DISABLE_ON_EXIT;

	// Inicializar componente
	inline virtual void initComponent() { tr = mngr->getComponent<Transform>(ent); }
};