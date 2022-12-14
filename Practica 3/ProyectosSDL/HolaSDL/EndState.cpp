#include "EndState.h"

EndState::EndState() : GameState() {
	
}

EndState::EndState(Game* g, bool win) : GameState(g){
	//Imagen correspondiente
	if (win) objects.push_back(new Menu(game->getTexture(Winner)));
	else objects.push_back(new Menu(game->getTexture(GameOver)));

	objects.push_back(new MenuButton(Vector2D(0,0), game->getTexture(RestartButton), game->newGame()));
}