#pragma once
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Component.h"

struct Health : public Component {
private:
	Texture* txt;
	int lifes;

public:
	Health(Texture* _t, int l = MAX_LIFES) : Component(), txt(_t), lifes(l) { }
};