#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"

class Health : public Component {
private:
	int lifes;
	Texture* texture;

public:
	// Constructora
	Health(Texture* _txt) : Component(), lifes(0), texture(_txt) { }

	// Métodos virtuales
	virtual void render();

	// Cambiar vidas
	void removeLife();
	void resetLifes();

	// Getter
	int checkLifes() { return lifes; }
};