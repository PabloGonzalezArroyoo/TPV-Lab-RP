#include "DisableOnExit.h"
#include "../ecs/Entity.h"
#include <iostream>

// Inicializa el componente, cogiendo el transform de la nave
void DisableOnExit::initComponent() {
	myTr = myObj->getComponent<Transform>();
}

// Comprobar si se sale de la pantalla para desactivar el objeto si es el caso
void DisableOnExit::update() {
	// Coger la posici�n
	Vector2D position = myTr->getPosition();

	// Si se sale por alg�n lateral de la pantalla, desactivarlo
	if (position.getX() < 0 - myTr->getWidth() || position.getX() > WIN_WIDTH
		|| position.getY() < 0 - myTr->getHeight() || position.getY() > WIN_HEIGHT) {
		myObj->setAlive(false);
	}
}