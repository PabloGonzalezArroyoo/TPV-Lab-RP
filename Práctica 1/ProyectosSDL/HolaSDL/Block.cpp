#include "Block.h"

// Constructora
Block::Block(Vector2D vector, uint width, uint height, uint colour, Texture* txt) {
	posAbs = vector; 
	w = width; h = height;
	color = colour; 
	texture = txt;
}

// Destructora
Block::~Block() {
	posAbs.~Vector2D();
	w = h = 0;
}

// Renderizado
void Block::render() {
	SDL_Rect dest;
	dest.x = (int) posAbs.getX(); dest.y = (int) posAbs.getY();
	dest.w = w; dest.h = h;

	//Calculamos la fila y la col del frame con el color
	uint fil = 0, col = 0;
	if (color > 3) { fil = 1; col = color - 4; }
	else { fil = 0; col = color - 1; }


	texture->renderFrame(dest, fil, col);
}