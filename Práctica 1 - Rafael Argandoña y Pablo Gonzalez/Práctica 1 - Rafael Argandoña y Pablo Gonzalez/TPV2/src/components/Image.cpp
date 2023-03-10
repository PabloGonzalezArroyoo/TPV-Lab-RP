#include "Image.h"
#include "../ecs/Entity.h"

// Nos guardamos una referencia al componente transform del jugador
void Image::initComponent() {
	tr = myObj->getComponent<Transform>();
}

// Pintamos
void Image::render() {
	texture->render(getRect(), tr->getRotation());
}

// Creamos la ventana destino en la que se pintará la textura
SDL_Rect Image::getRect() const{
	SDL_Rect r;
	r.x = tr->getPosition().getX();
	r.y = tr->getPosition().getY();
	r.w = tr->getWidth();
	r.h = tr->getHeight();

	return r;
}