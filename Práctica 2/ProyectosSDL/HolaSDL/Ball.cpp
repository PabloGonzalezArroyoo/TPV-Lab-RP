// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#include "Ball.h"
#include "Game.h"

// Constructora sobrecargada
Ball::Ball(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel, Game* _game) :
	MovingObject(_pos, _w, _h, _texture, _vel), game(_game) {}


// Actualiza la velocidad y la posición de la pelota en función de si colisiona o no
void Ball::update() {
	Vector2D colVector;
	if (game->collidesBall(getRect(), colVector)) {					// Comprobar si colisiona
		vel = vel - colVector * (2 * (vel * colVector));			// Obtener el vector de velocidad correspondiente
	}
	pos = pos + vel;												// Actualizamos la posición
}