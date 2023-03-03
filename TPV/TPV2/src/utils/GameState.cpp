#include "../game/GameState.h"

// Renderizado - llama a todos los renders de su lista de objetos
void GameState::render() {
	mng->render();
}

// Update - llama a todos los update de su lista de objetos
void GameState::update() {
	mng->update();
}

void GameState::refresh() {
	mng->refresh();
}