#pragma once
#include "GameObject.h"
#include "Exceptions.h"
#include <iostream>

const uint WIN_WITDH = 800, WIN_HEIGHT = 600, WALL_WIDTH = 15;

class ArkanoidObject : public GameObject
{
protected: 
	uint w, h;
	Vector2D pos;
	Texture* texture;

public:
	// Constructoras
	ArkanoidObject();
	ArkanoidObject(Vector2D _pos, uint _width, uint _height, Texture* _texture);
	virtual ~ArkanoidObject() {};

	// Métodos esenciales
	virtual void render();
	virtual void handleEvent(SDL_Event e) {};
	virtual bool collides(SDL_Rect rectBall, Vector2D& collisionVector) { return false; };

	// Guardado y lectura de archivo
	virtual void loadFromFile(istream& in, Texture* _texture);
	virtual void saveToFile(ostream& out);

	// Obtener el rectángulo de representación
	SDL_Rect getRect();
};

