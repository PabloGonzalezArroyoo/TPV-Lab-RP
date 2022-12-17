//Practica 3: Pablo Gonzalez Arroyo y Rafael Argandoña Blacido
#include "Reward.h"
#include "PlayState.h"

// Constructora vacía
Reward::Reward() : MovingObject(), r(0), c(0) , game(nullptr), type(' ') {}

// Constructora
Reward::Reward(Vector2D _pos, Texture* _texture, Vector2D _vel, char _type, PlayState* _game) :
	MovingObject(_pos, REWARD_WIDTH, REWARD_HEIGHT, _texture, _vel), type(_type), game(_game) {
	c = 0; r = 0;

	// Asignar la fila del tipo
	switch (type) {
		case 'L': r = 0; break;
		case 'R': r = 4; break;
		case 'E': r = 1; break;
		case 'S': r = 3; break;
	}
}

// Destructora
Reward::~Reward() {
	type = ' ';
	game = nullptr;
}

// Renderizado
void Reward::render() {
	texture->renderFrame(getRect(), r, c);
	c = (SDL_GetTicks() / 100) % 8;
}

// Actualiza la posición del reward de no haber chocado antes con la pala
void Reward::update() {
	if (PADDLE_AREA <= pos.getY() && game->collidesReward(getRect())) {
		if (pos.getY() < WIN_HEIGHT) game->rewardBehaviour(type);
		if (type != 'L') game->deleteReward(miPos);
	}
	else pos = pos + vel;
}

// Guardar en archivo
void Reward::saveToFile(ostream& out) {
	out << type << " ";
	MovingObject::saveToFile(out);
	out << " " << r << " " << c;
}

// Lectura de archivo
void Reward::loadFromFile(istream& in, Texture* _texture) {
	in >> type;
	MovingObject::loadFromFile(in, _texture);
	in >> r >> c;
}