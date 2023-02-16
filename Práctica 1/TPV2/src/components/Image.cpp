#include "Image.h"

void Image::initComponent() {
	tr = ent_->getComponent<Transform>(_TRANSFORM);
}

void Image::render() {
	texture->render(getRect());
}

SDL_Rect Image::getRect() const{
	SDL_Rect r;
	r.x = tr->getPosition().getX();
	r.y = tr->getPosition().getY();
	r.w = tr->getScale().getX();
	r.h = tr->getScale().getY();

	return r;
}