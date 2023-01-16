// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Constantes.h"
#include "checkML.h"

// INTERFAZ GAMEOBJECT:
// Propiedades: no gracias
// Métodos:
//		render -> método abstracto que será redefinido obligatoriamente por las clases hijas
//		update y handleEvent -> metodos virtuales que serán redefinidos por las clases hijas si es necesario

// Métodos abstractos [metodo() = 0] -> deben definirse SÍ O SÍ en las clases hijas sin ser definidas en la clase padre. Si una clase tiene un método
//										abstracto, esta se vuelve interfaz
// Métodos virtuales [virtual metodo();] -> pueden o no redefinirse en las clases hijas. Si no se redefinen, usan la implemtación del padre

typedef unsigned int uint;

class GameObject
{
public:
	// Constructora y destructora
	GameObject() {};
	virtual ~GameObject() {};

	// Métodos esenciales
	virtual void render() = 0;
	virtual void update() {};
	virtual void handleEvent(SDL_Event e) {};
};

