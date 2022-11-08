#pragma once
#include "GameObject.h"

class ArkanoidObject : public GameObject
{
protected: 
	uint w, h;
	Vector2D pos;
	Texture* texture;

public:

	ArkanoidObject();
	ArkanoidObject(Vector2D _pos, uint _width, uint _height, Texture* _texture);

	virtual void render();

	virtual void loadFromFile();

	virtual void saveToFile();

	SDL_Rect getRect();
};

