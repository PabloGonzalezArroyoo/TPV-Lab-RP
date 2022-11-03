#include "Paddle.h"
#include <iostream>

const int movVelocity = 15; // Velocidad de la paddle constante

// Constructora sobrecargada
Paddle::Paddle(Vector2D _pos, Vector2D _vel, uint _w, uint _h, Texture* _texture) {
	pos = _pos;
	w = _w;
	h = _h;
	vel = _vel;
	texture = _texture;
}

// Destructora - eliminamos punteros y reseteamos valores
Paddle::~Paddle() {
	pos = vel = Vector2D();
	w = h = 0;
	texture = nullptr;
}

// Renderizado de la textura de la pala entera
void Paddle::render() {
	texture->render(getDestRect());
}

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

// Comprobar colision [REVISAR Y HACER VECTOR UNITARIO (EL VERDADERO NORMALIZE)]
bool Paddle::collidesP(SDL_Rect rectBall, Vector2D& collisionVector) {
	if (SDL_HasIntersection(&rectBall, &getDestRect())) {								// Si intersecta
		if (rectBall.y <= pos.getY()) {													// Si la pelota choca por encima
			double ballCenter = (rectBall.x + rectBall.w / 2);							// Calcular el centro de la bola
			double paddleCenter = pos.getX() + w / 2;
			collisionVector = Vector2D((ballCenter - paddleCenter) / (w / 2), -2.5);
		}
		else {
			if (rectBall.x < pos.getX()) collisionVector = Vector2D(-1, -2.5);
			else collisionVector = Vector2D(1, -2.5);
		}
		return true;
	}
	return false;
}

// Devuelve el rectangulo destino, es decir, el del objeto en la escena con las dimensiones correspondientes
SDL_Rect Paddle::getDestRect() {
	SDL_Rect dest;
	dest.x = (int)pos.getX(); dest.y = (int)pos.getY();
	dest.w = w; dest.h = h;
	return dest;
}