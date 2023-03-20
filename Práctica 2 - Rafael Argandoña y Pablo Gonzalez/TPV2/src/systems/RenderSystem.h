#pragma once
#include "../ecs/System.h"
#include "../game/ecs_def.h"
#include "../sdlutils/Texture.h"
#include "../components/Transform.h"

class RenderSystem : public System {
public:
	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	virtual void receive(const Message& m) override;

	// Inicializar el sistema, etc.
	virtual void initSystem() override;

	// - Dibujar asteroides, balas y caza (s�lo si el juego no est� parado).
	// - Dibujar las vidas (siempre).
	// - Dibujar los mensajes correspondientes: si el juego est� parado, etc (como en
	// la pr�ctica 1)
	virtual void update() override;

private:
	// Para gestionar los mensajes correspondientes y actualizar los atributos
	// winner_ y state_. 
	void onRoundStart();
	void onRoundOver();
	void onGameStart();
	void onGameOver();

	SDL_Rect getRect(Transform* tr);

	//Uint8 winner_; // 0 - None, 1 - Asteroid, 2- Fighter
	//Uint8 state_; // El estado actual de juego (como en GameCtrlSystem)
};