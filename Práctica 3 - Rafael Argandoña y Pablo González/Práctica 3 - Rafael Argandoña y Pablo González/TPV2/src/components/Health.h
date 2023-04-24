#pragma once
#include "../ecs/Component.h"

struct Health : public Component {
private:
	int lifes;

public:
	constexpr static cmpId_type id = _HEALTH;

	Health(int l = MAX_LIFES) : Component(), lifes(l) { }
	int getLifes() { return lifes; };
	void setLives(int _l) { lifes = _l; }
};