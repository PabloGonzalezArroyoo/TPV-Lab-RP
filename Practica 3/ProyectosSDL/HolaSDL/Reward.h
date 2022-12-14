#pragma once
#include "MovingObject.h"
#include <list>

class PlayState; // Para solucionar la dependecia circular
class Reward : public MovingObject {
private:
	PlayState* game;
	char type; // L = nextLevel / R = extraLife / E/S = changePaddleSize
	uint r, c;
	list<GameObject*>::iterator miPos;

public:
	// Constructoras y destructor
	Reward();
	Reward(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel, char _type, PlayState* _game);
	~Reward();

	// Métodos esenciales
	virtual void render();
	virtual void update();

	// Lectura y guardado
	virtual void loadFromFile(istream& in, Texture* _texture);
	virtual void saveToFile(ostream& out);
	void setGameDepend(PlayState* _game) { game = _game; }
	void setIterator(list<GameObject*>::iterator _it) { miPos = _it; }

	// Obtener tipo
	char getType() { return type; };
};

