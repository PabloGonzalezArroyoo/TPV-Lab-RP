// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#include "Wall.h"
#include <iostream>

// Constructora sobrecargada
Wall::Wall(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _colVector) : 
	ArkanoidObject(_pos, _w, _h, texture), colVector(_colVector) {}

// Renderizado - pintamos toda la textura de la pared
void Wall::render() {
	texture->render(getRect());
}

// Comprobar colisiones
bool Wall::collidesW(SDL_Rect rectBall, Vector2D& collisionVector) {
	collisionVector = colVector;							// El vector colisión es el asignado a la pared correspondiente
	return SDL_HasIntersection(&rectBall, &getRect());  // Confirmar o negar colisión
}
