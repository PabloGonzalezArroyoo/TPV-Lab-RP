// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once
#include "ArkanoidObject.h"

// CLASE MOVINGOBJECT - PROTOTIPO DE UN ARKANOIDOBJECT CON MOVIMIENTO:
// Propiedades
//		- Hereda las de ArkanoidObject (w, h, pos y texture)
//		- vel: v�ctor de velocidad [(1, 0), (0, 1), etc]
// Metodos:
//		Constructora	-> Vac�a y sobrecargada tanto con los parametros necesarios
//		Destructora		-> Se ejecuta la destructora del padre
//		setPosition		-> coloca el objeto en una posicion recibida
//		getVelocity		-> devuelve el vector direcci�n del objeto
//		getPosition		-> devuelve la posici�n del objeto
//		loadFromFile	-> ejecuta el loadFromFile del padre y adem�s guarda los valores propios de esta clase (vel)
//		saveToFile		-> ejecuta el saveToFile del padre y adem�s carga los valores propios de esta clase (vel)

class MovingObject : public ArkanoidObject
{
protected:
	Vector2D vel;
public:
	//Constructora y destructora
	MovingObject();
	MovingObject(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel);
	virtual ~MovingObject() {};

	// M�todos esenciales
	virtual void update() {};

	// Getters y setters
	void setPosition(Vector2D _pos, Vector2D _vel);
	Vector2D getVelocity() { return vel; }
	Vector2D getPosition() { return pos; }

	// Guardado y cargado
	virtual void loadFromFile(istream& in, Texture* _texture);
	virtual void saveToFile(ostream& out);
};

