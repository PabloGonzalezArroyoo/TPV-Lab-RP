#include "BulletSystem.h"
#include "../ecs/Manager.h"

// Recivir mensajes
void BulletSystem::receive(const Message& m) {
	switch (m.id) {
		// Creaci�n de una bala
		case _m_CREATE_BULLET:
			shoot(mngr->getComponent<Transform>(mngr->getHandler(_hdlr_FIGHTER)));
			break;

		// Acabar la ronda
		case _m_ROUND_OVER:
			onRoundOver();
			break;
	}
}

// Mover las balas y comprobar si se salen
void BulletSystem::update() {
	// Cogemos el grupo de balas
	vector<Entity*> entities = mngr->getEntities(_grp_BULLETS);
	Transform* tr = nullptr;

	// Recorremos el grupo de balas
	for (int i = 0; i < entities.size(); i++) {
		// Pillamos el transform de esa bala
		tr = mngr->getComponent<Transform>(entities[i]);
		// Movemos la bala
		tr->setPosition(tr->getPosition() + tr->getVelocity());
		// Si queda fuera de los limites de la pantalla la desactivamos
		if (disableOnExit(tr)) mngr->setAlive(entities[i], false);
	}
}

// Comprueba si se salen de la pantalla
bool BulletSystem::disableOnExit(Transform* tr) {
	// Coger la posici�n
	Vector2D position = tr->getPosition();

	// Si se sale por alg�n lateral de la pantalla
	return position.getX() < 0 - tr->getWidth() || position.getX() > WIN_WIDTH
		|| position.getY() < 0 - tr->getHeight() || position.getY() > WIN_HEIGHT;
}

// Instancia una bala
void BulletSystem::shoot(Transform* tr) {
	//Creamos la bala
	Entity* b = mngr->addEntity(_grp_BULLETS);
	mngr->addComponent<Transform>(b, bulletPos(tr), BULLET_WIDTH, BULLET_HEIGTH, bulletVel(tr), tr->getRotation());
}

// Calcula la posici�n de la bala
Vector2D BulletSystem::bulletPos(Transform* pl) {
	// C�lculos del vector
	Vector2D bPos = pl->getPosition()
		+ Vector2D(pl->getWidth() / 2.0f, pl->getHeight() / 2.0f)
		- Vector2D(0.0f, pl->getHeight() / 2.0f + 5.0f + 12.0f).rotate(pl->getRotation())
		- Vector2D(2.0f, 10.0f);

	// Devolverlo
	return bPos;
}

// Calcula la velocidad de la bala
Vector2D BulletSystem::bulletVel(Transform* pl) {
	// C�lculos del vector
	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(pl->getRotation())
		* (pl->getVelocity().magnitude() + 5.0f);

	// Devolverlo
	return bVel;
}

// Desactiva la bala si colisiona con un asteroide
void BulletSystem::onCollision_BulletAsteroid(Entity* b) {
	// Desactiva la bala
	mngr->setAlive(b, false);
}

// Al acabar una ronda
void BulletSystem::onRoundOver() {
	// Elimina todas las balas presentes en escena
	mngr->removeEntities(_grp_BULLETS);
}
