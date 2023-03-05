#include "Gun.h"
#include "../sdlutils/InputHandler.h"
#include "Image.h"
#include "DisableOnEXit.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"

// Inicializa el componente, cogiendo el transform del objeto
void Gun::initComponent() {
	tr = myObj->getComponent<Transform>();
}

// Llama al manejo del input
void Gun::update() {
	handleInput();
}

// Procesamos el input del jugador
void Gun::handleInput() {
	// Aumentamos el cooldown de disparo
	lastShotTime = sdlutils().currRealTime() - startTime;

	// Si el jugador ha pulsado S para disparar y ya ha superado el cooldown
	if (InputHandler::instance()->isKeyDown(SDLK_s) && lastShotTime >= 250) {
		// Reproducimos el sonido de disparo y actualizamos el contador
		sound->play();
		startTime = sdlutils().currRealTime();

		//Creamos la bala
		Entity* b = myMng->addEntity(_grp_BULLETS);
		b->addComponent<Transform>(bulletPos(), bulletVel(), BULLET_WIDTH, BULLET_HEIGTH, tr->getRotation());
		b->addComponent<Image>(&sdlutils().images().at(FIRETXT));
		b->addComponent<DisableOnExit>();
	}
}

// Calcula la posición de la bala
Vector2D Gun::bulletPos() {
	// Cálculos del vector
	Vector2D bPos = tr->getPosition()
		+ Vector2D(tr->getWidth() / 2.0f, tr->getHeight() / 2.0f)
		- Vector2D(0.0f, tr->getHeight() / 2.0f + 5.0f + 12.0f).rotate(tr->getRotation())
		- Vector2D(2.0f, 10.0f);

	// Devolverlo
	return bPos;
}

// Calcula la velocidad de la bala
Vector2D Gun::bulletVel() {
	// Cálculos del vector
	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(tr->getRotation())
		* (tr->getVelocity().magnitude() + 5.0f);
	
	// Devolverlo
	return bVel;
}