#include "Wall.h"
#include <iostream>

// Constructora sobrecargada
Wall::Wall(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _colVector) {
	pos = _pos;
	w = _w;
	h = _h;
	texture = _texture;
	colVector = _colVector;
}

// Renderizado - pintamos toda la textura de la pared
void Wall::render() {
	texture->render(getDestRect());
}

// Comprobar colisiones
bool Wall::collidesW(SDL_Rect rectBall, Vector2D& collisionVector) {
	collisionVector = colVector;							// El vector colisión es el asignado a la pared correspondiente
	return SDL_HasIntersection(&rectBall, &getDestRect());  // Confirmar o negar colisión
}

// Devuelve el rectangulo destino, es decir, el del objeto en la escena con las dimensiones correspondientes
SDL_Rect Wall::getDestRect() {
	SDL_Rect dest;
	dest.x = (int)pos.getX(); dest.y = (int)pos.getY();
	dest.w = w; dest.h = h;
	return dest;
}