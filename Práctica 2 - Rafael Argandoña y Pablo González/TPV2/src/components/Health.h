#pragma once
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Component.h"

struct Health : public Component {
private:
	Texture* txt;
	int lifes;

public:
	constexpr static cmpId_type id = _HEALTH;

	Health(Texture* _t, int l = MAX_LIFES) : Component(), txt(_t), lifes(l) { }
};