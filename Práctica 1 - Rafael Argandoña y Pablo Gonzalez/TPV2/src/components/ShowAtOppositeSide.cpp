#include "ShowAtOppositeSide.h"
#include "../ecs/Entity.h"

// Inicializar el componente, cogiendo el transform del objeto
void ShowAtOppositeSide::initComponent() {
	tr = myObj->getComponent<Transform>();
}

// Comprobar si se sale de la pantalla, posicionando la nave en el lado contrario de esta
void ShowAtOppositeSide::update() {
	// Si se ha salido por la derecha
	if (tr->getPosition().getX() > WIN_WIDTH)
		tr->setPosition(Vector2D(0 - tr->getWidth(), tr->getPosition().getY()));

	// Si se ha salido por la izquierda
	else if (tr->getPosition().getX() < 0 - tr->getWidth())
		tr->setPosition(Vector2D(WIN_WIDTH, tr->getPosition().getY()));
	
	// Si se ha salido por arriba
	else if (tr->getPosition().getY() < 0 - tr->getHeight())
		tr->setPosition(Vector2D(tr->getPosition().getX(), WIN_HEIGHT));
	
	// Si se ha salido por abajo
	else if (tr->getPosition().getY() > WIN_HEIGHT)
		tr->setPosition(Vector2D(tr->getPosition().getX(), 0 - tr->getHeight()));
}