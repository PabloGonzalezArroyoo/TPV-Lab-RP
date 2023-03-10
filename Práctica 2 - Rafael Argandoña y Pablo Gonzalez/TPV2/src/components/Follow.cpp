#include "Follow.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

// Inicilizamos las referencias del componente cogiendo el transform del objeto y el del jugador
void Follow::initComponent() {
	myTr = myObj->getComponent<Transform>();
	plTr = myMng->getHandler(_hdlr_FIGHTER)->getComponent<Transform>();
}

void Follow::update() {
	// Calculamos la nueva velocidad y le asignamos una rotación adecuada
	Vector2D newVel = (plTr->getPosition() - myTr->getPosition()).normalize() * randomSpeed;
	newVel.rotate(newVel.angle(plTr->getPosition() - myTr->getPosition()) > 0 ? 1.0f : -1.0f);

	// Asignamos la nueva velocidad
	myTr->setVelocity(newVel);
}

