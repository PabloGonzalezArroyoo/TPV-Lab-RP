// Pr�ctica 1: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once

#include "MovingObject.h"

typedef unsigned int uint;

class Game; // Para solucionar la dependecia circular
class Ball : public MovingObject{
private:
	Game* game;

public:
	// Constructora
	Ball() { pos = vel = Vector2D(); texture = nullptr; w = h = 0; game = nullptr; };
	Ball(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel, Game* _game);

	// M�todos esenciales
	virtual void update();

	// Actualizar dependencias a game
	void setGameDepend(Game* _game) { game = _game; }
};