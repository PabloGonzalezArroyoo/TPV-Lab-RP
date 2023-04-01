#pragma once
#include "Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

struct Follow : public Component {
private:
	float randomSpeed;
public:
	constexpr static cmpId_type id = _FOLLOW;

	inline float getRandomSpeed() { return randomSpeed; }
};