// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once

#include "ArkanoidObject.h"

typedef unsigned int uint;

// CLASE BLOCK - OBJETO DEL JUEGO (ARKANOIDOBJECT):
// Propiedades:
//		- Heredada las de ArkanoidObject (w, h, texture, pos)
//		- color (int = {0, 1, 2, 3, 4, 5, 6})
// Metodos:
//		Constructora	-> Vac�a y con par�metros
//		Destructora		-> Se ejecuta la destructora del padre (ArkanoidObject)
//		render			-> Sobrecarga el metodo heredado de ArkanoidObject para pintar un frame de la imagen de Bloques, el del color correspondiente
//		collides		-> Procesa las colisiones de la pelota, calcul�ndo un vector director nuevo seg�n donde choca la bola que se le pasar� a esta
//		getColor		-> devuelve el color del bloque
//		getPosition		-> devuelve la posici�n

class Block : public ArkanoidObject{
private:
	uint color;

public:
	// Constructoras
	Block() { pos = Vector2D(); w = h = 0; color = 1; texture = nullptr; };
	Block(Vector2D _pos, uint _w, uint _h, uint _color, Texture* _texture);

	// M�todos esenciales
	virtual void render();

	// Colisiones
	bool collides(SDL_Rect rectBall, Vector2D& collisionVector);

	// Getters
	uint getColor() { return color; }
	Vector2D getPosition() { return pos; }
};

