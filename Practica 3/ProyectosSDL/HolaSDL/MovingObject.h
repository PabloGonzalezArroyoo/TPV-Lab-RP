// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once
#include "ArkanoidObject.h"

// CLASE MOVINGOBJECT - PROTOTIPO DE UN ARKANOIDOBJECT CON MOVIMIENTO:
// Propiedades
//		- Hereda las de ArkanoidObject (w, h, pos y texture)
//		- vel: véctor de velocidad [(1, 0), (0, 1), etc]
// Metodos:
//		Constructora	-> Vacía y sobrecargada tanto con los parametros necesarios
//		Destructora		-> Se ejecuta la destructora del padre
//		setPosition		-> coloca el objeto en una posicion recibida
//		getVelocity		-> devuelve el vector dirección del objeto
//		getPosition		-> devuelve la posición del objeto
//		loadFromFile	-> ejecuta el loadFromFile del padre y además guarda los valores propios de esta clase (vel)
//		saveToFile		-> ejecuta el saveToFile del padre y además carga los valores propios de esta clase (vel)

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

