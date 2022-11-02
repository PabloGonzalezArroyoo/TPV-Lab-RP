#include "Ball.h"
#include "Game.h"

Ball::Ball(Vector2D _pos, Vector2D _vel, uint _w, uint _h, Texture* _texture, Game* _game) {
	pos = _pos;
	vel = _vel;
	w = _w;
	h = _h;
	texture = _texture;
	game = _game;
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
		vel.normalize();
	}
	pos = pos + vel;
	
}

SDL_Rect Ball::getDestRect() {
	SDL_Rect dest;
	dest.x = (int)pos.getX(); dest.y = (int)pos.getY();
	dest.w = w; dest.h = h;
	return dest;
}