// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once

#include "checkML.h"
#include <cmath>

// CLASE VECTOR - PROPIEDAD DE OBJETOS DE LA APLICACI�N:
// Propiedades
//		- Hereda de MovingObject (w, h, pos, texture, vel)
//		- (x, y): componentes del vector
// M�todos:
//		Constructora	-> Vac�a y sobrecargada con los par�metros necesarios
//		getX/getY		-> devuelve la componente correspondiente
//		normalize		-> normaliza el vector
//		operadores		-> redefine los operadores de +, - y * para poder realizar operaciones correctamente
//		module			-> devuelve el m�dulo del vector

class Vector2D {
private:
	double x = 0, y = 0;

public:
	// Constructora y destructora
	Vector2D() { x = 0, y = 0; };
	Vector2D(double cordX, double cordY) { x = cordX; y = cordY; };

	// Devuelven las componentes del vector
	double getX() { return x; };
	double getY() { return y; };

	// Operaciones con el vector
	void normalize();
	Vector2D operator+(const Vector2D& other);
	Vector2D operator-(const Vector2D& other);
	double operator*(const Vector2D& other);	// Producto escalar
	Vector2D operator*(const double e);			// Vector por escalar

protected:
	double module() { return sqrt(pow(x, 2) + pow(y, 2)); };
};