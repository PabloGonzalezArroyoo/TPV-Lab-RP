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

// HandleEvent - llama a todos los handleEvent de su lista de objetos
void GameState::handleEvent(SDL_Event e) {
	for (GameObject* myObj : objects) myObj->handleEvent(e);
}