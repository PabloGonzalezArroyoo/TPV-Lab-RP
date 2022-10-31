#include "Ball.h"
#include "Game.h"

Ball::Ball(Vector2D v, Vector2D velocity, uint width, uint height, Texture* txt, Game* g) {
	pos = v;
	vel = velocity;
	w = width;
	h = height;
	texture = txt;
	game = g;
}

Ball::~Ball() {
	pos = vel = Vector2D();
	w = h = 0;
	texture = nullptr;
	game = nullptr;
}

void Ball::render() {
	texture->render(getDestRect());
}

void Ball::update() {
	Vector2D colVector;
	if (game->collides(getDestRect(), colVector)) {
		vel = vel - colVector * (2 * (vel * colVector));
	}
	pos = pos + vel;
}

SDL_Rect Ball::getDestRect() {
	SDL_Rect dest;
	dest.x = (int)pos.getX(); dest.y = (int)pos.getY();
	dest.w = w; dest.h = h;
	return dest;
}