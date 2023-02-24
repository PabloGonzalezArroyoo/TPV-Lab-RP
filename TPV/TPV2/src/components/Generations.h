#pragma once
#include "../ecs/Component.h"

class Generations : public Component {
private:
	int gen;

public:
	static const int id = _GENERATIONS;

	Generations(int g) : Component(), gen(g) { }

	// Setters y getters
	void setGeneration(int g) { gen = g; };
	int getGenerations() { return gen; };
};