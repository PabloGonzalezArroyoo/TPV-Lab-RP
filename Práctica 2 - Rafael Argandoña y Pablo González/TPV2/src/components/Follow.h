#pragma once
#include "Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

struct Follow : public Component {
private:
	Transform* myTr;
	Transform* plTr;
	float randomSpeed;
public:
	constexpr static cmpId_type id = _FOLLOW;

	inline virtual void initComponent() {
		myTr = mngr->getComponent<Transform>(ent);
		plTr = mngr->getComponent<Transform>(mngr->getHandler(_hdlr_FIGHTER));
		randomSpeed = sdlutils().rand().nextInt(1, 6) / 10.0f;
	}

	inline float getRandomSpeed() { return randomSpeed; }
};