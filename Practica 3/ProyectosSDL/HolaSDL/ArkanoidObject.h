// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once
#include "GameObject.h"
#include "Exceptions.h"
#include <iostream>

//	CLASE BASE DE TODOS LOS OBJETOS DEL JUEGO
// Propiedades:
//		- Dimensiones (w y h)
//		- Posicion (x, y) 
//		- Puntero a mi textura (clase para poder pintarme en el mundo)
// Métodos:
//		Constructora vacía y normal -> la vacía setea todo a cero y a nullptr, la normal recibe los parámetros
//		Destructora					-> virtual y vacia para las clases "hijas"
//		render						-> virtual y vacío, herdado de GameObject (render para frame estático)
//		handleEvent					-> virtual y vacia para que las clases "hijas" decidan como manejar los diferentes eventos
//		loadFromFile				-> carga de un archivo junto a una textura recibida y crea el objeto con los parámetros básicos
//		saveToFile					-> metodo que guarda en un archivo (recibido abierto como parametro) la informacion que se puede encontrar 
//									en referencia al objeto en esta clase
//		getRect						-> devuelve la ventana de representacion del objeto en el mundo del juego

class ArkanoidObject : public GameObject
{
protected: 
	uint w, h;
	Vector2D pos;
	Texture* texture;

public:
	// Constructoras
	ArkanoidObject();
	ArkanoidObject(Vector2D _pos, uint _width, uint _height, Texture* _texture);
	virtual ~ArkanoidObject() {};

	// Métodos esenciales
	virtual void render();
	virtual void handleEvent(SDL_Event e) {};
	virtual bool collides(SDL_Rect rectBall, Vector2D& collisionVector) { return false; };

	// Guardado y lectura de archivo
	virtual void loadFromFile(istream& in, Texture* _texture);
	virtual void saveToFile(ostream& out);

	// Obtener el rectángulo de representación
	SDL_Rect getRect();
};

