#include "Health.h"

// Renderizar coracones por pantalla
void Health::render() {
	// Crear el rectangulo fuente
	SDL_Rect r;
	r.x = UPPER_LEFT_CORNER_X;		// Posiciones fijas
	r.y = UPPER_LEFT_CORNER_Y;
	r.w = texture->width() / 4;
	r.h = texture->height() / 4;

	// Renderizar tantos corazones como número de vidas tenga el jugador
	for (int i = 0; i < lifes; i++) {
		r.x = (r.w * i) + 10;
		texture->render(r);
	}
}

// Decrecemos el numero de vidas del objeto
void Health::removeLife() {
	--lifes;
}

// Devolvemos el valor de las vidas al máximo posible
void Health::resetLifes() {
	lifes = MAX_LIFES;
}