#include "PlayState.h"
#include "../components/Image.h"

PlayState::PlayState(Game* g) : GameState(g), paused(false), gameOver(false) {
	Manager* myM = new Manager();
	auto player = myM->addEntity();
	player->addComponent<Transform>(_TRANSFORM, Vector2D(WIN_WIDTH / 2, WIN_HEIGHT/2), Vector2D(0,0), 64, 64);
	player->addComponent<Image>(_IMAGE);

	mng = myM;
}