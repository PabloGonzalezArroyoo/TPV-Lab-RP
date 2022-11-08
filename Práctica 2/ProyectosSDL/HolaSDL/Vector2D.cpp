// Pr�ctica 1: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#include "Vector2D.h"
#include <cmath>

// Normaliza el vector para volverlo unitario
void Vector2D::normalize() {
	x /= module();
	y /= module();
}

// Devuelve un nuevo vector que es el resultado de la suma de otros dos
Vector2D Vector2D::operator+(const Vector2D& other) {
	return Vector2D(x + other.x, y + other.y);
}

// Devuelve un nuevo vector que es el resultado de la resta de otros dos
Vector2D Vector2D::operator-(const Vector2D& other) {
	return Vector2D(x - other.x, y - other.y);
}

// Devuelve el producto escalar de dos vectores
double Vector2D::operator*(const Vector2D& other) {
	return x * other.x + y * other.y;
}

// Devuelve un nuevo vector que es el resultado de multiplicarlo por un valor
Vector2D Vector2D::operator*(const double e) {
	return Vector2D(x * e, y * e);
}