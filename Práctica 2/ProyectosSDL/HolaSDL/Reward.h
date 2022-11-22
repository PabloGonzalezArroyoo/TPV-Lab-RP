#pragma once
#include "MovingObject.h"

class Game; // Para solucionar la dependecia circular
class Reward : public MovingObject {
private:
	Game* game;
	char type; // n = nextLevel / e = extraLife / c = changePaddleSize

public:
	Reward() { pos = vel = Vector2D(); w = h = 0; texture = nullptr; game = nullptr; type = ' '; }
	Reward(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel, char _type, Game* _game);

	bool collidesR(SDL_Rect rectPaddle);
	char getType() { return type; };
	virtual void render();
	virtual void update();
};

