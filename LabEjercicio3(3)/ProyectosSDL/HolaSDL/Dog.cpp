#include "Dog.h"
#include "Texture.h"

Dog::Dog(Texture* txt) {
	myTexture = txt;					// Puntero a textura
	row = txt->getNumRows();			// Filas y columnas de la textura
	col = txt->getNumCols();
	dest.x = dest.y = 0;				// Posici�n del rect�ngulo destino
	dest.w = txt->getW() / col;			// Dimensi�n del rect�ngulo destino
	dest.h = txt->getH() / row;
}

Dog::~Dog()
{
	SDL_DestroyTexture(myTexture->getTexture());
}

void Dog::render() {
	myTexture->renderFrame(dest, row, col);
	if (col >= 0 && col < 5) col++;
	else col = 0;
}

void Dog::move(int winW, int winH) {
	if (!stop) {
		if (dest.x >= winW) dest.x = 0;
		if (dest.y >= winH) dest.y = 0;
		else {
			dest.x += vx; dest.y += vy;
		}
	}
}

void Dog::handleEvents(SDL_Event event) {
	if (event.key.keysym.sym == SDLK_d) stop = !stop;	// Parar/reanudar el perro si se pulsa la tecla d
	else if (event.key.keysym.sym == SDLK_f) { mov /= 2; anim /= 2; }
	else if (event.key.keysym.sym == SDLK_s) { mov *= 2; anim *= 2; }
}