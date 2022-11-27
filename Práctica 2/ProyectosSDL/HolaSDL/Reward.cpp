#include "Reward.h"
#include "Game.h"

const int WIN_HEIGHT = 800;
const int PADDLE_AREA = WIN_HEIGHT - 30;

Reward::Reward(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel, char _type, Game* _game) :
	MovingObject(_pos, _w, _h, _texture, _vel), type(_type), game(_game) {
	c = 0; r = 0;
	switch (type) {
		case 'L': r = 0; break;
		case 'R': r = 4; break;
		case 'E': r = 1; break;
		case 'S': r = 3; break;
	}
}

Reward::~Reward() {
	type = ' ';
	game = nullptr;
}

void Reward::render() {
	texture->renderFrame(getRect(), r, c);
	c = (SDL_GetTicks() / 100) % 8;
}

void Reward::update() {
	if (pos.getY() >= WIN_HEIGHT) game->collidesReward( getRect(), type); // te mueres
	// else if (PADDLE_AREA <= pos.getY() && game->collidesReward(getRect())); // dar premio
	pos = pos + vel;
}

void Reward::saveToFile(ostream& out) {
	out << w << " " << h << " " << pos.getX() << " " << pos.getY() << " ";
	out << vel.getX() << " " << vel.getY() << " ";
	out << type << " " << r << " " << c;
}

