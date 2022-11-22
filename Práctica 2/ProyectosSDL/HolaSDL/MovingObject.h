#pragma once
#include "ArkanoidObject.h"

class MovingObject : public ArkanoidObject
{
protected:
	Vector2D vel;
public:
	//Constructora
	MovingObject();
	MovingObject(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel);

	virtual ~MovingObject() {};

	void setPosition(Vector2D _pos, Vector2D _vel);

	virtual void update() {};
};

