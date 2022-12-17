// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once

#include "MovingObject.h"

typedef unsigned int uint;

class PlayState; // Para solucionar la dependecia circular
class Ball : public MovingObject{
private:
	PlayState* game;

public:
	// Constructora
	Ball() { pos = vel = Vector2D(); texture = nullptr; w = h = 0; game = nullptr; };
	Ball(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel, PlayState* _game);

	// M�todos esenciales
	virtual void update();

	// Actualizar dependencias a game
	void setGameDepend(PlayState* _game) { game = _game; }
};