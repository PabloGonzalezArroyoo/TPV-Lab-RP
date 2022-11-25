// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#include "Block.h"
#include <iostream>

// Constructora sobrecargada
Block::Block(Vector2D _pos, uint _w, uint _h, uint _color, Texture* _texture) :
ArkanoidObject(_pos, _w, _h, _texture), color(_color) {}

// Renderizado
void Block::render() {
	// Calculamos la fila y la col del frame con el color
	uint fil = 0, col = 0;
	if (color > 3) { fil = 1; col = color - 4; }
	else { fil = 0; col = color - 1; }

	// Renderizamos el frame correspondiente al color del bloque
	texture->renderFrame(getRect(), fil, col);
}

// Comprobamos colision
bool Block::collides(SDL_Rect rectBall, Vector2D& collisionVector) {
	SDL_Rect intersection;															// Área de intersección resultante de la pelota y el bloque que colisionan
	SDL_Rect rectBlock = getRect();												// Rectángulo del bloque

	if (SDL_IntersectRect(&rectBall, &rectBlock, &intersection)) {					// Si han colisionado, obtener área de interseccion
		
		if (intersection.w > intersection.h) {										// Si el área es más ancha que alta, ha colisionado con las caras horizontales
			if (rectBall.y < rectBlock.y) collisionVector = Vector2D(0, -1);		// Arriba
			else if (rectBall.y > rectBlock.y) collisionVector = Vector2D(0, 1);	// Abajo
		}
		else if (intersection.w < intersection.h) {									// Si el área es más alta que ancha, ha colisionado con las caras verticales
			if (rectBall.x < rectBlock.x) collisionVector = Vector2D(-1, 0);		// Izquierda
			else if (rectBall.x > rectBlock.x) collisionVector = Vector2D(1, 0);	// Derecha
		}
		return true;																// Confirmar colisión
	}
	return false;																	// Negar colisión
}

void Block::loadFromFile(istream in, Texture* _texture) {
	in >> w >> h;
	int newX, newY;
	in >> newX >> newY;
	pos = Vector2D(newX, newY);

	texture = _texture;

	in >> color;
}

void Block::saveToFile(ostream& out) {
	out << w << " " << h << " " << pos.getX() << " " << pos.getY() << " ";
	out << color << " ";
}