#include "GameState.h"

GameState::~GameState() {
	for (GameObject* myObj : objects) delete(myObj);
}

// Renderizado - llama a todos los renders de su lista de objetos
void GameState::render() {
	for(GameObject* myObj : objects) myObj->render();
}

// Update - llama a todos los update de su lista de objetos
void GameState::update() {
	for (GameObject* myObj : objects) myObj->update();
}

// HandleEvent - llama a todos los handleEvents de su lista de objetos
void GameState::handleEvent(SDL_Event e) {
	bool control = false;										// Booleano de control para saber si ya hemos encontrado el boton pulsado
	list<GameObject*>::iterator it = next(objects.begin());		// Iterador para recorrer los botones 

	while (!control && it != objects.end()) {					// Mientras que ningun boton se ha pulsado y sigan quedando por revisar
		MenuButton* myB = dynamic_cast<MenuButton*> (*it);		// Cambiamos el objeto a tipo boton para acceder
		control = myB->handleEvents(e);							// a su metodo handleEvents, que nos devuelve si se ha pulsado o no
		if (!control) it++;										// Si el boton no ha sido pulsado, avanzamos en la lista
	}
}