// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once

#include "MovingObject.h"

typedef unsigned int uint;

// CLASE BALL - OBJETO DEL JUEGO (ArkanoidObject && MovingObject):
// Propiedades:
//		- Heredada las de ArkanoidObject y las de MovingObject (w, h, texture, pos && vel)
//		- PlayState: referencia al estado del juego (donde siempre va a existir)
// Métodos:
//		Constructora	-> Vacía y con parámetros
//		Destructora		-> Se ejecuta la destructora del padre (ArkanoidObject)
//		update			-> Actualiza las propiedades del objeto en tiempo de ejecucion (posición y direccion segun haya chocado o no)
//		setGameDepend	-> Setea el puntero al juego (ya que desde la lectura de archivo no se puede hacer de primeras)

class PlayState; // Para solucionar la dependecia circular
class Ball : public MovingObject {
private:
	PlayState* game;

public:
	// Constructora
	Ball() { pos = vel = Vector2D(); texture = nullptr; w = h = 0; game = nullptr; };
	Ball(Vector2D _pos, uint _w, uint _h, Texture* _texture, Vector2D _vel, PlayState* _game);

	// Métodos esenciales
	virtual void update();

	// Actualizar dependencias a game
	void setGameDepend(PlayState* _game) { game = _game; }
};