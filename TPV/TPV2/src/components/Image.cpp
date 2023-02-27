#include "Image.h"
#include "../ecs/Entity.h"

void Image::initComponent() {
	tr = myObj->getComponent<Transform>();
}

void Image::render() {
	texture->render(getRect(), tr->getRotation());
}

SDL_Rect Image::getRect() const{
	SDL_Rect r;
	r.x = tr->getPosition().getX();
	r.y = tr->getPosition().getY();
	r.w = tr->getWidth();
	r.h = tr->getHeight();

	return r;
}