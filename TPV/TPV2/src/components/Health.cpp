#include "Health.h"

void Health::render() {
	SDL_Rect r;
	r.x = UPPER_LEFT_CORNER_X;
	r.y = UPPER_LEFT_CORNER_Y;
	r.w = texture->width() / 4;
	r.h = texture->height() / 4;

	for (int i = 0; i < lifes; i++) {
		r.x = (r.w * i) + 10;
		texture->render(r);
	}
}

void Health::removeLife() {
	--lifes;
}

void Health::resetLifes() {
	lifes = MAX_LIFES;
}