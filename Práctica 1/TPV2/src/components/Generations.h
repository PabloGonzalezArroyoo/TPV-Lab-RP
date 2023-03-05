#pragma once
#include "../ecs/Component.h"

class Generations : public Component {
private:
	// Variable para almacenar la generación del asteroide
	int gen;

public:
	// Id del componente
	constexpr static cmpId_type id = _GENERATIONS;

	// Constructora
	Generations(int g) : Component(), gen(g) { }

	// Setters y getters
	void setGeneration(int g) { gen = g; };
	int getGenerations() { return gen; };
};