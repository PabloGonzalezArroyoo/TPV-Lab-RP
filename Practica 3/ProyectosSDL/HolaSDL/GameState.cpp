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
	bool control = false;
	list<GameObject*>::iterator it = next(objects.begin());

	while (!control && it != objects.end()) {
		MenuButton* myB = dynamic_cast<MenuButton*> (*it);
		control = myB->handleEvents(e);
		if (!control) it++;
	}
}