#include "BulletSystem.h"
#include "../ecs/Manager.h"

void BulletSystem::receive(const Message& m) {

}

void BulletSystem::initSystem() {
}

void BulletSystem::shoot(Transform* tr) {
	//Creamos la bala
	Entity* b = mngr->addEntity(_grp_BULLETS);
	mngr->addComponent<Transform>(b, bulletPos(tr), BULLET_WIDTH, BULLET_HEIGTH, bulletVel(tr), tr->getRotation());
	mngr->addComponent<DisableOnExit>(b);
}

// Calcula la posición de la bala
Vector2D BulletSystem::bulletPos(Transform* pl) {
	// Cálculos del vector
	Vector2D bPos = pl->getPosition()
		+ Vector2D(pl->getWidth() / 2.0f, pl->getHeight() / 2.0f)
		- Vector2D(0.0f, pl->getHeight() / 2.0f + 5.0f + 12.0f).rotate(pl->getRotation())
		- Vector2D(2.0f, 10.0f);

	// Devolverlo
	return bPos;
}

// Calcula la velocidad de la bala
Vector2D BulletSystem::bulletVel(Transform* pl) {
	// Cálculos del vector
	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(pl->getRotation())
		* (pl->getVelocity().magnitude() + 5.0f);

	// Devolverlo
	return bVel;
}

void BulletSystem::onCollision_BulletAsteroid(Entity* b) {
	mngr->setAlive(b, false);
}

void BulletSystem::onRoundOver() {
	mngr->removeEntities(_grp_BULLETS);
}

void BulletSystem::onRoundStart() {
}