// Pr�ctica 1: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#include "Paddle.h"
#include <iostream>

const int MOV_VEL= 15; // Velocidad de la paddle constante

// Constructora sobrecargada
Paddle::Paddle(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel) :
	MovingObject(_pos, _w, _h, _texture, _vel), dir(0)
 {}


// Calcular velocidad seg�n la direcci�n y aplicar comprobando que no sobrepasa los l�mites
void Paddle::update() {
	vel = Vector2D(dir, 0) * MOV_VEL;													// Crear vector direcci�n
	if (pos.getX() + vel.getX() > WALL_WIDTH && pos.getX() + vel.getX() < WIN_WITDH - WALL_WIDTH - w) pos = pos + vel; // Comprobar y aplicar
}

// Comprobar si se han pulsado teclas que activan un comportamiento en la pala
void Paddle::handleEvent(SDL_Event e) {
	if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT) { dir = 1;  update(); dir = 0; }		// Si pulsamos "d" o "->", x++
	else if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT) { dir = -1; update(); dir = 0; }	// Si pulsados "a" o "<-", x--															// Si no se pulsa nada, se queda quieto
}

// Comprobar colision
bool Paddle::collides(SDL_Rect rectBall, Vector2D& collisionVector) {
	if (SDL_HasIntersection(&rectBall, &getRect())) {									// Si intersecta
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

// Cambio de dimensiones de la pala (usado al recibir las rewards E � S)
void Paddle::changeDimensions(bool elongate) {
	if (elongate) {									// Alargar
		if (w + 15 > MAX_WIDTH) w = MAX_WIDTH;		// Comprobar si se supera el m�ximo, y ajustar a �l si se da el caso
		else w += 15;
	}
	else {											// Acortar
		if (w - 15 < MIN_WIDTH) w = MIN_WIDTH;		// Comprobar si se supera el m�nimo, y ajustar a �l si se da el caso
		else w -= 15;
	}
}