#pragma once
#include "../ecs/System.h"

#include "../components/FighterCtrl.h"
#include "../components/Follow.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../components/Health.h"
#include "../components/Transform.h"

#include "../utils/Collisions.h"

class CollisionsSystem : public System {
public:
	constexpr static sysId_type id = _sys_COLLISIONS;

	// Comprobar colisiones como en la práctica 1 y enviar mensajes correspondientes.
	void update() override;

	void receive(const Message& m) override;

private:
	void checkCollisions();

	bool collisionAsteroidsFighter(Entity* player, Transform* astTr);

	bool collisionAsteroidsBullets(Transform* astTr);
	
	STATE st;
};