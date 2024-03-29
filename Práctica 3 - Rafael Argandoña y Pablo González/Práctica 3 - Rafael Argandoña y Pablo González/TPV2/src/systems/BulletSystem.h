#pragma once
#include "../ecs/System.h"

#include "../components/FighterCtrl.h"
#include "../components/Follow.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../components/Health.h"
#include "../components/Transform.h"

class BulletSystem : public System {
public:
	constexpr static sysId_type id = _sys_BULLET;

	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;

	// Si el juego est� parado no hacer nada, en otro caso mover las balas y
	// desactivar las que salen de la ventana como en la pr�ctica 1.
	void update() override;

private:
	// Movemos las balas
	void moveBullets(grpId group);

	// Para gestionar el mensaje de que el jugador ha disparado. A�adir una bala al
	// juego, como en la pr�ctica 1. Recuerda que la rotaci�n de la bala ser�a
	// vel.angle(Vector2D(0.0f,-1.0f))
	void shoot(Transform* tr, grpId group);

	// Calcular posici�n y velocidad
	Vector2D bulletPos(Transform* pl);
	Vector2D bulletVel(Transform* pl);

	// Para gestionar el mensaje de que ha habido un choque entre una bala y un
	// asteroide. Desactivar la bala �b�.
	void onCollision_BulletAsteroid(Entity* b);

	// Deshabilitar si se salen de la pantalla
	bool disableOnExit(Transform* tr);

	// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todas las
	// balas, y desactivar el sistema.
	void onRoundOver();
};