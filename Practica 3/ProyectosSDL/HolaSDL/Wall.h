// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once

#include "ArkanoidObject.h"

typedef unsigned int uint;

// CLASE WALL - OBJETO DEL JUEGO:
// Propiedades
//		- Hereda de ArkanoidObject (w, h, pos, texture)
//		- colVector: vector a devolver cuando se colisiona con ella (vector normal)
// Métodos:
//		Constructora	-> Vacía y sobrecargada con los parámetros necesarios
//		Destructora		-> Llama a su destructora
//		collides		-> si intersecta la pelota con la pared, devuelve si intersecta y cambia el vector colisión de pelota
//		loadFromFile	-> carga la pared a partir de un archivo de texto
//		saveToFile		-> guarda la información de la pared en un archivo de texto

class Wall : public ArkanoidObject{
private:
	Vector2D colVector;

public:
	// Constructora y destructor
	Wall() { pos = Vector2D(); w = 0, h = 0; texture = nullptr; colVector = Vector2D(0, 0); };
	Wall(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _colVector);

	// Métodos esenciales
	virtual bool collides(SDL_Rect rectBall, Vector2D& colV);

	// Cargar y guardar
	virtual void loadFromFile(istream& in, Texture* _texture);
	virtual void saveToFile(ostream& out);
};

