#include "Ball.h"
#include "Game.h"

// Constructora
Ball::Ball(Vector2D _pos, Vector2D _vel, uint _w, uint _h, Texture* _texture, Game* _game) {
	pos = _pos;
	vel = _vel;
	w = _w;
	h = _h;
	texture = _texture;
	game = _game;
}

// Destructora
Ball::~Ball() {
	pos = vel = Vector2D();
	w = h = 0;
	texture = nullptr;
	game = nullptr;
}

// Renderizado
void Ball::render() {
	texture->render(getDestRect());
}

// Actualiza la velocidad y la posición de la pelota en función de si colisiona o no.
void Ball::update() {
	Vector2D colVector;
	if (game->collides(getDestRect(), colVector)) {					// Comprobar si colisiona
		vel = vel - colVector * (2 * (vel * colVector));			// Obtener el vector de velocidad correspondiente
		vel.normalize();											// Normalizar el vector
	}
	cout << "vel: (" << vel.getX() << ", " << vel.getY() << ")" << endl;
	pos = pos + vel;												// Aplicar velocidad
}

// Devuelve el rectangulo destino, es decir, el del objeto en la escena
SDL_Rect Ball::getDestRect() {
	SDL_Rect dest;
	dest.x = (int)pos.getX(); dest.y = (int)pos.getY();
	dest.w = w; dest.h = h;
	return dest;
}