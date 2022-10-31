#include "Paddle.h"
#include <iostream>

const int movVelocity = 10;

// Constructora
Paddle::Paddle(Vector2D v, int width, int height, Vector2D velocity, Texture* txt, Vector2D colV) {
	pos = v; w = width; h = height; vel = velocity; texture = txt; colVector = colV;
}

Paddle::~Paddle() {
	pos = vel = Vector2D();
	w = h = 0;
	texture = nullptr;
}

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
	else if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT) update(-1);	// Si pulsados "a" o "<-", x--;
	else update(0);																		// Si no se pulsa nada, se queda quieto
}

bool Paddle::collidesP(SDL_Rect rectBall, Vector2D& collisionVector) {
	collisionVector = colVector;
	return SDL_HasIntersection(&rectBall, &getDestRect());
}

SDL_Rect Paddle::getDestRect() {
	SDL_Rect dest;
	dest.x = (int)pos.getX(); dest.y = (int)pos.getY();
	dest.w = w; dest.h = h;
	return dest;
}