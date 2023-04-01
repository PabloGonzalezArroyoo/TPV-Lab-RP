#pragma once
#include "../ecs/System.h"

#include "../components/FighterCtrl.h"
#include "../components/Follow.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../components/Health.h"
#include "../components/Transform.h"

#include "../sdlutils/InputHandler.h"

class FighterSystem : public System {
public:
	constexpr static sysId_type id = _sys_FIGHTER;

	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	void receive(const Message& m) override;

	// Crear la entidad del caza, añadir sus componentes, asociarla con un handler
	// correspondiente, etc.
	void initSystem() override;

	// Si el juego está parado no hacer nada, en otro caso actualizar la velocidad
	// del caza y moverlo como en la práctica 1 (acelerar, desacelerar, etc). Además, 
	// si el juego no está parado y el jugador pulsa la tecla de disparo, enviar un
	// mensaje con las características físicas de la bala. Recuerda que se puede disparar
	// sólo una bala cada 0.25sec.
	void update() override;

private:

	// Para gestionar el mensaje de que ha acabado una ronda. Desactivar el sistema.
	void onRoundOver();

	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema.
	void onRoundStart();

	void setFighterVelocity(Transform* tr, FighterCtrl* fc);

	Vector2D deAccelerate(Vector2D vel);

	void showAtOppositeSide(Transform* tr);

	float cooldown, startTime;
	float lastSoundTime, soundTime;
};