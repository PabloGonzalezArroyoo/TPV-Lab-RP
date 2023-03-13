#pragma once
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

struct Gun : public Component {
private:
	Transform* tr;
public:
	constexpr static cmpId_type id = _GUN;

	inline virtual void initComponent() { tr = mngr->getComponent<Transform>(ent); }
};