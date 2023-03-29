#include "CollisionsSystem.h"
#include "../ecs/Manager.h"
#include "../components/Generations.h"

void CollisionsSystem::receive(const Message& m) {

}

void CollisionsSystem::initSystem() {
	onRoundStart();
}

void CollisionsSystem::update() {
	checkCollisions();
}

void CollisionsSystem::checkCollisions() {
	vector<Entity*> asts = mngr->getEntities(_grp_ASTEROIDS);
	Entity* pl = mngr->getHandler(_hdlr_FIGHTER);

	Transform* astTr = nullptr;

	bool plCollided = !mngr->isAlive(pl);

	for (int i = 0; i < asts.size() && !plCollided; i++) {
		if (mngr->isAlive(asts[i])) {
			astTr = mngr->getComponent<Transform>(asts[i]);
			plCollided = collisionAsteroidsFighter(pl, astTr);
			
			if (!plCollided && collisionAsteroidsBullets(astTr)) {
				Message m;
				m.id = _m_ASTEROID_COLLIDED;
				m.asteroid_collided_data.e = asts[i];
				mngr->send(m);
			}
		}
	}

	if (plCollided) {
		// MANDAR MENSAJE DE Q MATARON A UN INOCENTE
		Message m;
		
	}
}

bool CollisionsSystem::collisionAsteroidsFighter(Entity* player, Transform* astTr) {
	bool collision = !mngr->isAlive(player);

	Transform* plTr = mngr->getComponent<Transform>(player);

	collision = Collisions::collidesWithRotation(
		plTr->getPosition(), plTr->getWidth(), plTr->getHeight(), plTr->getRotation(),
		astTr->getPosition(), astTr->getWidth(), astTr->getHeight(), astTr->getRotation());

	return collision;
}

bool CollisionsSystem::collisionAsteroidsBullets(Transform* astTr) {
	bool collision = false;
	auto bllts = mngr->getEntities(_grp_BULLETS);
	Transform* blltTr = nullptr;

	for (int i = 0; i < bllts.size() && !collision; i++) {
		if (mngr->isAlive(bllts[i])) {
			blltTr = mngr->getComponent<Transform>(bllts[i]);

			collision = Collisions::collidesWithRotation(
				blltTr->getPosition(), blltTr->getWidth(), blltTr->getHeight(), blltTr->getRotation(),
				astTr->getPosition(), astTr->getWidth(), astTr->getHeight(), astTr->getRotation());
			if (collision) 
				mngr->setAlive(bllts[i], false);
		}
	}
	return collision;
}

void CollisionsSystem::onRoundOver() { }

void CollisionsSystem::onRoundStart() { }