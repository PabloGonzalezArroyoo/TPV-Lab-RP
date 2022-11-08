// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#include "Paddle.h"
#include <iostream>

const int movVelocity = 15; // Velocidad de la paddle constante

// Constructora sobrecargada
Paddle::Paddle(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel) :
	MovingObject(_pos, _w, _h, _texture, _vel)
 {}


// Calcular velocidad según la dirección y aplicar comprobando que no sobrepasa los límites
void Paddle::update(int dir, uint const& winW, uint const& wallW) {
	vel = Vector2D(dir, 0) * movVelocity;												// Crear vector dirección
	if (pos.getX() + vel.getX() > wallW && pos.getX() + vel.getX() < winW - wallW - w) pos = pos + vel; // Comprobar y aplicar
}

// Comprobar si se han pulsado teclas que activan un comportamiento en la pala
void Paddle::handleEvents(SDL_Event e, uint const& winW, uint const& wallW) {
	if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT) update(1, winW, wallW);		// Si pulsamos "d" o "->", x++
	else if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT) update(-1, winW, wallW);	// Si pulsados "a" o "<-", x--															// Si no se pulsa nada, se queda quieto
}

// Comprobar colision
bool Paddle::collidesP(SDL_Rect rectBall, Vector2D& collisionVector) {
	if (SDL_HasIntersection(&rectBall, &getRect())) {								// Si intersecta
		if (rectBall.y <= pos.getY()) {													// Si la pelota choca por encima
			double ballCenter = (rectBall.x + rectBall.w / 2);							// Calcular el centro de la bola
			double paddleCenter = pos.getX() + w / 2;
			collisionVector = Vector2D((ballCenter - paddleCenter) / (w / 2), -2.5);
		}
		else {																			// Si da por los lados
			if (rectBall.x < pos.getX()) collisionVector = Vector2D(-1, -2.5);			// Izquierda
			else collisionVector = Vector2D(1, -2.5);									// Derecha
		}
		collisionVector.normalize();													// Normalizar el vector
		return true;
	}
	return false;
}
