// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once
#include "MovingObject.h"
#include <list>

// CLASE PADDLE - OBJETO DEL JUEGO:
// Propiedades
//		- Hereda de MovingObject (w, h, pos, texture, vel)
//		- game: puntero al juego
//		- type: carácter (L, R, E, S) que determina el tipo de reward que es
//		- r y c: fila y columna para la animación
//		- miPos: iterador a la posición de la reward en la lista de objetos en la escena
// Métodos:
//		Constructora	-> Vacía y sobrecargada con los parámetros necesarios
//		Destructora		-> Llama a su destructora
//		render			-> renderiza la animación de la reward según r y c
//		update			-> mueve la reward en sentido descendente
//		loadFromFile	-> carga la reward a partir de un archivo de texto
//		saveToFile		-> guarda la información de la reward en un archivo de texto
//		setGameDepend	-> método usado para la carga a partir de un archivo de texto donde se asigna el puntero al juego
//		setIterator		-> actualiza el iterador miPos
//		getType			-> devuelve el tipo de la reward

class PlayState; // Para solucionar la dependecia circular
class Reward : public MovingObject {
private:
	PlayState* game;
	char type; // L = nextLevel / R = extraLife / E/S = changePaddleSize
	uint r, c;
	list<GameObject*>::iterator miPos;

public:
	// Constructoras y destructor
	Reward();
	Reward(Vector2D _pos, Texture* _texture, Vector2D _vel, char _type, PlayState* _game);
	~Reward();

	// Métodos esenciales
	virtual void render();
	virtual void update();

	// Lectura y guardado
	virtual void loadFromFile(istream& in, Texture* _texture);
	virtual void saveToFile(ostream& out);
	void setGameDepend(PlayState* _game) { game = _game; }
	void setIterator(list<GameObject*>::iterator it) { miPos = it; }

	// Obtener tipo
	char getType() { return type; };
};

