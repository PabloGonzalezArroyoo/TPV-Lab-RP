// Pr�ctica 1: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
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
	SDL_Rect intersection;															// �rea de intersecci�n resultante de la pelota y el bloque que colisionan
	SDL_Rect rectBlock = getRect();												// Rect�ngulo del bloque

	if (SDL_IntersectRect(&rectBall, &rectBlock, &intersection)) {					// Si han colisionado, obtener �rea de interseccion
		
		if (intersection.w > intersection.h) {										// Si el �rea es m�s ancha que alta, ha colisionado con las caras horizontales
			if (rectBall.y < rectBlock.y) collisionVector = Vector2D(0, -1);		// Arriba
			else if (rectBall.y > rectBlock.y) collisionVector = Vector2D(0, 1);	// Abajo
		}
		else if (intersection.w < intersection.h) {									// Si el �rea es m�s alta que ancha, ha colisionado con las caras verticales
			if (rectBall.x < rectBlock.x) collisionVector = Vector2D(-1, 0);		// Izquierda
			else if (rectBall.x > rectBlock.x) collisionVector = Vector2D(1, 0);	// Derecha
		}
		return true;																// Confirmar colisi�n
	}
	return false;																	// Negar colisi�n
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