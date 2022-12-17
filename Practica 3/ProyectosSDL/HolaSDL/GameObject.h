// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Constantes.h"
#include "checkML.h"

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

