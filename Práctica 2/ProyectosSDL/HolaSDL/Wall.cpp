// Pr�ctica 1: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#include "Wall.h"
#include <iostream>

// Constructora sobrecargada
Wall::Wall(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _colVector) : 
	ArkanoidObject(_pos, _w, _h, _texture), colVector(_colVector) {}

// Comprobar colisiones
bool Wall::collidesW(SDL_Rect rectBall, Vector2D& collisionVector) {
	collisionVector = colVector;							// El vector colisi�n es el asignado a la pared correspondiente
	return SDL_HasIntersection(&rectBall, &getRect());  // Confirmar o negar colisi�n
}
