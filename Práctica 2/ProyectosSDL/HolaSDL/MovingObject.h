#pragma once
#include "ArkanoidObject.h"

class MovingObject : public ArkanoidObject
{
protected:
	Vector2D vel;
public:
	//Constructora y destructora
	MovingObject();
	MovingObject(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel);
	virtual ~MovingObject() {};

	// Métodos esenciales
	virtual void update() {};

	// Getters y setters
	void setPosition(Vector2D _pos, Vector2D _vel);
	Vector2D getVelocity() { return vel; }
	Vector2D getPosition() { return pos; }

	// Guardado y cargado
	virtual void loadFromFile(istream& in, Texture* _texture);
	virtual void saveToFile(ostream& out);
};

