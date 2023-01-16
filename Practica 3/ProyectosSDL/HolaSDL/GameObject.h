// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Constantes.h"
#include "checkML.h"

// INTERFAZ GAMEOBJECT:
// Propiedades: no gracias
// M�todos:
//		render -> m�todo abstracto que ser� redefinido obligatoriamente por las clases hijas
//		update y handleEvent -> metodos virtuales que ser�n redefinidos por las clases hijas si es necesario

// M�todos abstractos [metodo() = 0] -> deben definirse S� O S� en las clases hijas sin ser definidas en la clase padre. Si una clase tiene un m�todo
//										abstracto, esta se vuelve interfaz
// M�todos virtuales [virtual metodo();] -> pueden o no redefinirse en las clases hijas. Si no se redefinen, usan la implemtaci�n del padre

typedef unsigned int uint;

class GameObject
{
public:
	// Constructora y destructora
	GameObject() {};
	virtual ~GameObject() {};

	// M�todos esenciales
	virtual void render() = 0;
	virtual void update() {};
	virtual void handleEvent(SDL_Event e) {};
};

