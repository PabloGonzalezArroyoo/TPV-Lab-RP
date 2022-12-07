#pragma once
#include "MovingObject.h"

class Game; // Para solucionar la dependecia circular
class Reward : public MovingObject {
private:
	Game* game;
	char type; // L = nextLevel / R = extraLife / E/S = changePaddleSize
	uint r, c;

public:
	// Constructoras y destructor
	Reward();
	Reward(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel, char _type, Game* _game);
	~Reward();

	// Métodos esenciales
	virtual void render();
	virtual void update();

	// Lectura y guardado
	virtual void loadFromFile(istream& in, Texture* _texture);
	virtual void saveToFile(ostream& out);
	void setGameDepend(Game* _game) { game = _game; }

	// Obtener tipo
	char getType() { return type; };
};

