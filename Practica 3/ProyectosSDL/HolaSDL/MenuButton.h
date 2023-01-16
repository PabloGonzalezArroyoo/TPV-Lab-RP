// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once
#include "GameObject.h"

// CLASE MENUBUTTON - OBJETO BOTON DE LA APLICACION:
// Propiedades:
//		- pos : vector de posici�n en la pantalla
//		- texture: puntero a mi textura
//		- state : estado actual del bot�n
//		- myC: funci�n de tipo Callback que ejecutar� el bot�n al ser pulsado
//		- game: puntero al juego para acceder a la m�quina de estados
// M�todos:
//		Constructora	-> normal y sobrecargada con los valores necesarios
//		render			-> calcula mi ventana de representaci�n en la pantalla y pinta un frame u otro dependiendo del estado
//		handleEvents	-> informa de si se ha pulsado sobre �l y ejecuta la funci�n correspondiente (la del Callback)
//		update			-> comprueba la posici�n del rat�n para cambiar el estado del mismo (estado = onOver)
//		getState		-> devuelve el estado del bot�n (int)

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
	
	// M�todos eneciales
	virtual void render();
	bool handleEvents(SDL_Event e);
	virtual void update();

	// Getter
	int getState() { return state; }
};

