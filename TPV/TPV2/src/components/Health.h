#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"

class Health : public Component {
private:
	// Referencia a la textura de las vidas
	Texture* texture;
	// Variable del numero de vidas
	int lifes;

public:
	// Id del componente
	constexpr static cmpId_type id = _HEALTH;

	// Constructora
	Health(Texture* _txt, int _l = MAX_LIFES) : Component(), lifes(_l), texture(_txt) { }

	// Métodos virtuales
	virtual void render();

	// Cambiar vidas
	void removeLife();
	void resetLifes();

	// Getter
	int checkLifes() { return lifes; }
};