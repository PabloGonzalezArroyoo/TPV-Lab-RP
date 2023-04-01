#include "CollisionsSystem.h"
#include "../ecs/Manager.h"

void CollisionsSystem::update() {
	checkCollisions();
}

// Comprueba las colisiones entre asteroide y player/bullet
void CollisionsSystem::checkCollisions() {
	// Coger asteroides y la nave
	vector<Entity*> asts = mngr->getEntities(_grp_ASTEROIDS);
	Entity* pl = mngr->getHandler(_hdlr_FIGHTER);

	Transform* astTr = nullptr;

	// Booleano de parada (si el jugador a colisionado -> si está vivo)
	bool plCollided = !mngr->isAlive(pl);

	// Recorrer asteroides
	for (int i = 0; i < asts.size() && !plCollided; i++) {
		// Si el asteroide sigue vivo
		if (mngr->isAlive(asts[i])) {
			astTr = mngr->getComponent<Transform>(asts[i]);

			// Comprobar colisión con el jugador
			plCollided = collisionAsteroidsFighter(pl, astTr);
			
			// Si no ha colisionado con el jugador, comprobar si lo hace con la bala y mandar mensajes en casoa afirmativo
			if (!plCollided && collisionAsteroidsBullets(astTr)) {
				Message m1;
				m1.id = _m_PLAY_SOUND;
				m1._sound_data.sound = &sdlutils().soundEffects().at(EXPLOSION);
				mngr->send(m1);
				
				Message m2;
				m2.id = _m_ASTEROID_COLLIDED;
				m2.asteroid_collided_data.e = asts[i];
				mngr->send(m2);
			}
		}
	}

	// Si ha colisionado con el jugador, mandar mensajes correspondientes
	if (plCollided) {
		Message m1;
		m1.id = _m_PLAY_SOUND;
		m1._sound_data.sound = &sdlutils().soundEffects().at(OOF);
		mngr->send(m1);
		SDL_Delay(1000);

		Message m2;
		m2.id = _m_PLAYER_DAMAGED;
		mngr->send(m2, true);
	}
}

bool CollisionsSystem::collisionAsteroidsFighter(Entity* player, Transform* astTr) {
	// Pillamos el transform del player
	Transform* plTr = mngr->getComponent<Transform>(player);
	// Comprobamos si asteroide y nave colisionan
	bool collision = Collisions::collidesWithRotation(
		plTr->getPosition(), plTr->getWidth(), plTr->getHeight(), plTr->getRotation(),
		astTr->getPosition(), astTr->getWidth(), astTr->getHeight(), astTr->getRotation());
	// Devulvemos la comprobacion
	return collision;
}

// Comprobar si un asteroide colisiona con alguna bala
bool CollisionsSystem::collisionAsteroidsBullets(Transform* astTr) {
	bool collision = false;
	// Cogemos el grupo de balas
	auto bllts = mngr->getEntities(_grp_BULLETS);
	Transform* blltTr = nullptr;

	// Recorremos el grupo
	for (int i = 0; i < bllts.size() && !collision; i++) {
		// Si sigue activada
		if (mngr->isAlive(bllts[i])) {
			// Pillamos el transform
			blltTr = mngr->getComponent<Transform>(bllts[i]);
			// Comprobamos si colisiona con el asteroide
			collision = Collisions::collidesWithRotation(
				blltTr->getPosition(), blltTr->getWidth(), blltTr->getHeight(), blltTr->getRotation(),
				astTr->getPosition(), astTr->getWidth(), astTr->getHeight(), astTr->getRotation());
			// Si lo hace, desactivo la bala
			if (collision) 
				mngr->setAlive(bllts[i], false);
		}
	}
	return collision;
}