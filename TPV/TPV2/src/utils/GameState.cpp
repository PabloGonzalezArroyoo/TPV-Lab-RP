#include "../game/GameState.h"

// Destructora - Elimina el manager
GameState::~GameState() {
	delete mng;
}
// Renderizado - llama a todos los renders de su lista de objetos
void GameState::render() {
	mng->render();
}

// Update - llama a todos los update de su lista de objetos
void GameState::update() {
	mng->update();
}

// Refresh - llama al metodo del manager qu elimina los objetos marcados para ello
void GameState::refresh() {
	mng->refresh();
}