// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once

#include "ArkanoidObject.h"

typedef unsigned int uint;

// CLASE BLOCK - OBJETO DEL JUEGO (ARKANOIDOBJECT):
// Propiedades:
//		- Heredada las de ArkanoidObject (w, h, texture, pos)
//		- color (int = {0, 1, 2, 3, 4, 5, 6})
// Metodos:
//		Constructora	-> Vacía y con parámetros
//		Destructora		-> Se ejecuta la destructora del padre (ArkanoidObject)
//		render			-> Sobrecarga el metodo heredado de ArkanoidObject para pintar un frame de la imagen de Bloques, el del color correspondiente
//		collides		-> Procesa las colisiones de la pelota, calculándo un vector director nuevo según donde choca la bola que se le pasará a esta
//		getColor		-> devuelve el color del bloque
//		getPosition		-> devuelve la posición

class Block : public ArkanoidObject{
private:
	uint color;

public:
	// Constructoras
	Block() { pos = Vector2D(); w = h = 0; color = 1; texture = nullptr; };
	Block(Vector2D _pos, uint _w, uint _h, uint _color, Texture* _texture);

	// Métodos esenciales
	virtual void render();

	// Colisiones
	bool collides(SDL_Rect rectBall, Vector2D& collisionVector);

	// Getters
	uint getColor() { return color; }
	Vector2D getPosition() { return pos; }
};

