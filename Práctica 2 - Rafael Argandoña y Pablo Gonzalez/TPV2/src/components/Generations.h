#pragma once
#include "../ecs/Component.h"

struct Generations : public Component {
private: 
	int gen;
public:
	constexpr static cmpId_type id = _GENERATIONS;

	Generations(int g) : Component(), gen(g) { }

	// GETTERS
	int getGenerations() { return gen;	}
};