#pragma once
#include "../ecs/System.h"
#include "../game/ecs_def.h"
#include "../sdlutils/Texture.h"


#include "../components/FighterCtrl.h"
#include "../components/Follow.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../components/Health.h"
#include "../components/Transform.h"

class RenderSystem : public System {
public:
	constexpr static sysId_type id = _sys_RENDER;

	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	virtual void receive(const Message& m) override;

	// Inicializar el sistema, etc.
	virtual void initSystem() override;

	// - Dibujar asteroides, balas y caza (sólo si el juego no está parado).
	// - Dibujar las vidas (siempre).
	// - Dibujar los mensajes correspondientes: si el juego está parado, etc (como en
	// la práctica 1)
	virtual void update() override;

private:
	// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_. 
	void onRoundStart();
	void onRoundOver();
	void onGameStart();
	void onGameOver();

	void renderGroup(grpId_type group, string key) const;
	void renderAsteroids();
	void renderTexts() const;
	void renderUI() const;

	float startTime;
	STATE state;
};