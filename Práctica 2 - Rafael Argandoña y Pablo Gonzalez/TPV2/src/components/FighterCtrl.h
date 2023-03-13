#pragma once
#include "../ecs/Manager.h"
#include "Transform.h"

struct FighterCtrl : public Component {
private:
	Transform* tr;
	
	float thrust;
	int r;
	float speedLimit;

public:
	constexpr static cmpId_type id = _FIGHTERCTRL;

	// Inicializar componente
	inline virtual void initComponent() { 
		tr = mngr->getComponent<Transform>(ent);
		thrust = 0.2;
		r = 0;
		speedLimit = 1.5;
	}
};