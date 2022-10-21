#pragma once
class Vector2D
{
private:
	double x = 0, y = 0;

public:
	// Constructora y destructora
	Vector2D() { x = 0, y = 0; };
	Vector2D(double cordX, double cordY) { x = cordX; y = cordY; };
	~Vector2D() { x = 0; y = 0; };

	// Devuelven las componentes del vector
	double getX() { return x; };
	double getY() { return y; };

	// Operaciones con el vector
	double normalize();
	Vector2D operator+(const Vector2D& other);
	Vector2D operator-(const Vector2D& other);
	double operator*(const Vector2D& other);	// Producto escalar
	Vector2D operator*(const double e);			// Vector por escalar
};