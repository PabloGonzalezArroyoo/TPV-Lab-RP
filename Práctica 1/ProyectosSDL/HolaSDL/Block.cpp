#include "Block.h"
#include <iostream>

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
	texture = nullptr;
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

bool Block::collides(SDL_Rect rectBall, Vector2D& collisionVector) {
	if (SDL_HasIntersection(&rectBall, &getDestRect())) {
		if (rectBall.x < posAbs.getX()) collisionVector = Vector2D(-1, 0);			// Izquierda
		else if (rectBall.x >= posAbs.getX() + w) collisionVector = Vector2D(1, 0);	//Derecha
		else {
			if (rectBall.y < posAbs.getY()) collisionVector = Vector2D(0, -1);		// Cara superior
			else collisionVector = Vector2D(0, 1);									// Cara inferior
		}
		return true;
	}
	return false;
}

SDL_Rect Block::getDestRect() {
	SDL_Rect dest;
	dest.x = (int)posAbs.getX(); dest.y = (int)posAbs.getY();
	dest.w = w; dest.h = h;
	return dest;
}