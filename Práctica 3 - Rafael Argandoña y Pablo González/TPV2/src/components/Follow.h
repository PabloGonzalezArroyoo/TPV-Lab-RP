#pragma once
#include "Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

struct Follow : public Component {
private:
	float randomSpeed;
public:
	constexpr static cmpId_type id = _FOLLOW;

	virtual void initComponent() { randomSpeed = sdlutils().rand().nextInt(1, 6) / 10.0f; }

	inline float getRandomSpeed() { return randomSpeed; }
};