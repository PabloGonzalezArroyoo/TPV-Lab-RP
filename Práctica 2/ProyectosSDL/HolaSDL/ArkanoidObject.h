#pragma once
#include "GameObject.h"
#include <iostream>

class ArkanoidObject : public GameObject
{
protected: 
	uint w, h;
	Vector2D pos;
	Texture* texture;

public:

	ArkanoidObject();
	ArkanoidObject(Vector2D _pos, uint _width, uint _height, Texture* _texture);
	// ArkanoidObject(istream in, Texture* _texture);
	virtual ~ArkanoidObject() {};

	virtual void render();

	virtual void handleEvent(SDL_Event e) {};

	virtual void loadFromFile(istream& in, Texture* _texture);

	virtual void saveToFile(ostream& out);

	SDL_Rect getRect();
};

