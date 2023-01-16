// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once
#include "GameObject.h"

// CLASE MENUBUTTON - OBJETO BOTON DE LA APLICACION:
// Propiedades:
//		- pos : vector de posición en la pantalla
//		- texture: puntero a mi textura
//		- state : estado actual del botón
//		- myC: función de tipo Callback que ejecutará el botón al ser pulsado
//		- game: puntero al juego para acceder a la máquina de estados
// Métodos:
//		Constructora	-> normal y sobrecargada con los valores necesarios
//		render			-> calcula mi ventana de representación en la pantalla y pinta un frame u otro dependiendo del estado
//		handleEvents	-> informa de si se ha pulsado sobre él y ejecuta la función correspondiente (la del Callback)
//		update			-> comprueba la posición del ratón para cambiar el estado del mismo (estado = onOver)
//		getState		-> devuelve el estado del botón (int)

class Game;
typedef void Callback (Game* game);

enum ButtonState { OnOut, OnOver, OnClick };

class MenuButton : public GameObject
{
private:
	Vector2D pos;
	Texture* texture;
	int state;
	Callback* myC;
	Game* game;

public:
	// Constructora
	MenuButton();
	MenuButton(Vector2D _pos, Texture* _txt, Callback* _c, Game* g);
	
	// Métodos eneciales
	virtual void render();
	bool handleEvents(SDL_Event e);
	virtual void update();

	// Getter
	int getState() { return state; }
};

