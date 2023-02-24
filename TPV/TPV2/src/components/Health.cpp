#include "Health.h"

void Health::render() {
	SDL_Rect r;
	r.x = UPPER_LEFT_CORNER_X;
	r.y = UPPER_LEFT_CORNER_Y;
	r.w = texture->width();
	r.h = texture->height();

	for (int i = 0; i < lifes; i++) {
		r.x += (r.w * i) + 10;
		texture->render(r);
	}
}

void Health::removeLife() {
	--lifes;
}

void Health::resetLifes() {
	lifes = MAX_LIFES;
}