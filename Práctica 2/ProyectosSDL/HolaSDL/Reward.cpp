#include "Reward.h"
#include "Game.h"

const int WIN_HEIGHT = 800;
const int PADDLE_AREA = WIN_HEIGHT - 30;

Reward::Reward(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel, char _type, Game* _game) :
	MovingObject(_pos, _w, _h, _texture, _vel), type(_type), game(_game) {}

void Reward::render() {
	texture->render(getRect());
}

void Reward::update() {
	if (pos.getY() >= WIN_HEIGHT); // te mueres
	// else if (PADDLE_AREA <= pos.getY() && game->collidesReward(getRect())); // dar premio
	pos = pos + vel;
}

