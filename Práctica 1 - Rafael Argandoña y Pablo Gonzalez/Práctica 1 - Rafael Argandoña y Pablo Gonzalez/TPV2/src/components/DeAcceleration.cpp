#include "DeAcceleration.h"
#include "../ecs/Entity.h"

// Inicializa el componente, cogiendo el transform de la nave
void DeAcceleration::initComponent() {
	tr = myObj->getComponent<Transform>();
}

// Decelera la nave hasta poner su velocidad a cero
void DeAcceleration::update() {
	// Cogemos la velocidad
	Vector2D newVelocity = tr->getVelocity();

	// Si el vector de velocidad es mayor o igual 0.05, debemos decelerarlo
	if (newVelocity.magnitude() >= 0.05) {
		// Decrementamos la velocidad un 0,5%
		newVelocity = newVelocity * 0.995;

		// Si la maginitud, tras el decremento, pasa a ser menor que 0.05, la asignamos a cero
		if (newVelocity.magnitude() <= 0.05) newVelocity = Vector2D();

		// Aplicar la velocidad
		tr->setVelocity(newVelocity);
	}
}