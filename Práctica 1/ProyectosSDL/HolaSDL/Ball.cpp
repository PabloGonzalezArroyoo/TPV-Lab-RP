// Práctica 1: Pablo González Arroyo, Rafael Argandoña Blácido
#include "Ball.h"
#include "Game.h"

// Constructora sobrecargada
Ball::Ball(Vector2D _pos, Vector2D _vel, uint _w, uint _h, Texture* _texture, Game* _game) {
	pos = _pos;
	vel = _vel;
	w = _w;
	h = _h;
	texture = _texture;
	game = _game;
}

// Renderizado - pintamos toda la textura de la bola
void Ball::render() {
	texture->render(getDestRect());
}

// Actualiza la velocidad y la posición de la pelota en función de si colisiona o no
void Ball::update() {
	Vector2D colVector;
	if (game->collides(getDestRect(), colVector)) {					// Comprobar si colisiona
		vel = vel - colVector * (2 * (vel * colVector));			// Obtener el vector de velocidad correspondiente
	}
	pos = pos + vel;												// Actualizamos la posición
}

// Cambia la posición de la bola y la velocidad a la incial del juego (usado para cambio de niveles)
void Ball::setPosition(Vector2D _pos, Vector2D _vel) {
	pos = _pos;
	vel = _vel;
}

// Devuelve el rectangulo destino, es decir, el del objeto en la escena con las dimensiones correspondientes
SDL_Rect Ball::getDestRect() {
	SDL_Rect dest;
	dest.x = (int)pos.getX(); dest.y = (int)pos.getY();
	dest.w = w; dest.h = h;
	return dest;
}