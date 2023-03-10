#include "FighterCtrl.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "../game/Game.h"
#include "../game/PauseState.h"

FighterCtrl::FighterCtrl(Game* g, SoundEffect* _sound) : Component(), game(g), tr(nullptr),
					thrust(0.2), r(0), speedLimit(1.5), sound(_sound),
					startTime(sdlutils().currRealTime()), lastSoundTime(0) { }

// Inicializar el componente, cogiendo el transform del objeto
void FighterCtrl::initComponent() {
	tr = myObj->getComponent<Transform>();
}

// Llama al manejo del input
void FighterCtrl::update() {
	handleInput();
}

// Procesamos el input del jugador
void FighterCtrl::handleInput() {

	// Reproducir sonido de movimiento correctamente pasados unos milisegundos
	lastSoundTime = sdlutils().currRealTime() - startTime;

	// Si ha pulsado la flecha izquierda rotamos la nave hacia la izquierda
	if (InputHandler::instance()->isKeyDown(SDLK_LEFT)) {
		r = (r - 2) % 360;
		tr->setRotation(r);
	}
	// Si ha pulsado la flecha derecha rotamos la nave hacia la derecha
	else if (InputHandler::instance()->isKeyDown(SDLK_RIGHT)) {
		r = (r + 2) % 360;
		tr->setRotation(r);
	}
	
	// Si se ha pulsado hacia arriba
	if (InputHandler::instance()->isKeyDown(SDLK_UP)) {
		if (lastSoundTime >= 500) {sound->play(); startTime = sdlutils().currRealTime(); }
		
		// Calcular el vector velocidad
		Vector2D vel = tr->getVelocity() + Vector2D(0, -1).rotate(r) * thrust;

		// Si sobrepasa el limite de velocidad, restringirlo
		if (vel.magnitude() > speedLimit) vel = vel.normalize() * speedLimit;

		// Setear la velocidad
		tr->setVelocity(vel);
	}

	// Si se ha pulsado la tecla ESCAPE lanzamos el estado de pausa
	if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
		game->getStateMachine()->pushState(new PauseState(game, myObj->getComponent<Health>()->checkLifes()));
	}
}