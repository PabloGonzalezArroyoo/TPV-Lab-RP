#include "Paddle.h"
#include <iostream>

const int movVelocity = 15;

// Constructora
Paddle::Paddle(Vector2D _pos, Vector2D _vel, uint _w, uint _h, Texture* _texture, Vector2D _colVector) {
	pos = _pos;
	w = _w;
	h = _h;
	vel = _vel;
	texture = _texture;
	colVector = _colVector;
}

// Destructora
Paddle::~Paddle() {
	pos = vel = Vector2D();
	w = h = 0;
	texture = nullptr;
}

// Renderizado
void Paddle::render() {
	SDL_Rect dest;
	dest.x = (int)pos.getX(); dest.y = (int)pos.getY();
	dest.w = w; dest.h = h;
	texture->render(dest);
}

void Paddle::update(int dir) {
	vel = Vector2D(dir, 0) * movVelocity;												// Crear vector dirección
	if (pos.getX() + vel.getX() > 15 && pos.getX() + vel.getX() < 800 - 15 - w) pos = pos + vel; // Aplicarlo
}

void Paddle::handleEvents(SDL_Event e) {
	if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT) update(1);		// Si pulsamos "d" o "->", x++
	else if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT) update(-1);	// Si pulsados "a" o "<-", x--
	else update(0);																		// Si no se pulsa nada, se queda quieto
}

bool Paddle::collidesP(SDL_Rect rectBall, Vector2D& collisionVector) {
	collisionVector = colVector;
	if (SDL_HasIntersection(&rectBall, &getDestRect())) {
		if (pos.getX() <= rectBall.x && rectBall.x <= pos.getX() + w / 3) { // Diagonal izquierda
			cout << "---" << endl;
			cout << "rectBall: (" << rectBall.x << ", " << rectBall.y << ")" << endl;
			cout << "rectPaddle: (" << getDestRect().x << ", " << getDestRect().y << ")" << endl;
			collisionVector = Vector2D(-1, -1);
		}
		else if (pos.getX() + w / 3 <= rectBall.x && rectBall.x <= pos.getX() + 2 * w / 3) collisionVector = Vector2D(0, -1);	// Centro
		else if (pos.getX() + 2 * w / 3 <= rectBall.x && rectBall.x <= pos.getX() + w) collisionVector = Vector2D(1, -1);	// Diagonal derecha
		return true;
	}
	return false;
}

SDL_Rect Paddle::getDestRect() {
	SDL_Rect dest;
	dest.x = (int)pos.getX(); dest.y = (int)pos.getY();
	dest.w = w; dest.h = h;
	return dest;
}

/*if (SDL_HasIntersection(&rectBall, &getDestRect())) {
		if (pos.getX() <= rectBall.x <= pos.getX() + w/3) collisionVector = Vector2D(-1, -1);			// Diagonal izquierda
		else if (pos.getX() + w / 3 <= rectBall.x <= pos.getX() + 2*w/3) collisionVector = Vector2D(0, -1);	// Centro
		else collisionVector = Vector2D(1, -1);															// Diagonal derecha
		return true;
	}
	return false;*/