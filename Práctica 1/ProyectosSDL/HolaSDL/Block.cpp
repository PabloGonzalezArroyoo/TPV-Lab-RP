#include "Block.h"

// Constructora
Block::Block(Vector2D vector, uint width, uint height, uint rows, uint cols, uint colour, Texture* txt) {
	posAbs = vector; 
	w = width; h = height; 
	r = rows; c = cols; 
	color = colour; 
	texture = txt;
}

// Destructora
Block::~Block() {
	posAbs.~Vector2D();
	w = h = 0;
	texture->wipe();
	delete(texture);
}

// Renderizado
void Block::render() {
	SDL_Rect dest;
	dest.x = (int) posAbs.getX(); dest.y = (int) posAbs.getY();
	dest.w = w; dest.h = h;

	texture->render(dest);
}