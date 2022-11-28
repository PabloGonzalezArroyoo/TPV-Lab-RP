#pragma once
#include "MovingObject.h"

class Game; // Para solucionar la dependecia circular
class Reward : public MovingObject {
private:
	Game* game;
	char type; // n = nextLevel / e = extraLife / c = changePaddleSize
	uint r, c;

public:
	Reward();
	Reward(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel, char _type, Game* _game);
	~Reward();

	char getType() { return type; };
	virtual void render();
	virtual void update();

	virtual void loadFromFile(istream& in, Texture* _texture);
	virtual void saveToFile(ostream& out);

	void setGameDepend(Game* _game) { game = _game; }
};

