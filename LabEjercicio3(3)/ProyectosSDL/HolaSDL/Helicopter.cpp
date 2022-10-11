#include "Helicopter.h"
#include "Texture.h"

Helicopter::Helicopter(Texture* txt) {
	myTexture = txt;					// Puntero a textura
	row = txt->getNumRows();			// Filas y columnas de la textura
	col = txt->getNumCols();
	dest.x = dest.y = 0;				// Posición del rectángulo destino
	dest.w = txt->getW() / col;			// Dimensión del rectángulo destino
	dest.h = txt->getH() / row;
}

Helicopter::~Helicopter()
{
	SDL_DestroyTexture(myTexture->getTexture());
}

void Helicopter::render() {
	myTexture->renderFrame(dest, row, col);
	if (col >= 0 && col < 4) col++;
	else col = 0;
}

void Helicopter::move(int winW, int winH) {
	if (!stop) {
		if (dest.x >= winW) dest.x = 0;
		if (dest.y >= winH) dest.y = 0;
		else {
			dest.x += vx; dest.y += vy;
		}
	}
}

void Helicopter::handleEvents(SDL_Event event) {
	if (event.key.keysym.sym == SDLK_h) stop = !stop;	// Parar/reanudar el helicoptero si se pulsa la tecla d
	else if (event.key.keysym.sym == SDLK_j) { mov /= 2; anim /= 2; }
	else if (event.key.keysym.sym == SDLK_g) { mov *= 2; anim *= 2; }
}