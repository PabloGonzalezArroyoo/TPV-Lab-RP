#include "PlayState.h"
#include "../components/Image.h"

PlayState::PlayState(Game* g) : GameState(g), paused(false), gameOver(false) {
	mng = new Manager();
	auto player = mng->addEntity();
	player->addComponent<Transform>(Vector2D(WIN_WIDTH / 2, WIN_HEIGHT/2), Vector2D(0,0), 64, 64);
	player->addComponent<Image>();
}

PlayState::~PlayState() {
	delete mng;
}