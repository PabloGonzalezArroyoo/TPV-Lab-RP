#include "PlayState.h"
#include "Game.h"

PlayState::PlayState(Game* g) : GameState(g), paused(false), gameOver(false) {
	mng = new Manager();
	auto player = mng->addEntity();
	player->addComponent<Transform>(Vector2D(WIN_WIDTH / 2, WIN_HEIGHT/2), Vector2D(0,0), 85, 77);
	player->addComponent<Image>(g->getTexture(FIGTHER));
	player->addComponent<FighterCtrl>();
	player->addComponent<DeAcceleration>();
	player->addComponent<ShowAtOppositeSide>();
	player->addComponent<Gun>(g);

	mng->setHandler(_hdlr_FIGHTER, player);

	astController = new AsteroidsController(mng, game);
	astController->createAsteroids(10);
}

PlayState::~PlayState() {
	delete mng;
}

void PlayState::update() {
	GameState::update();
	astController->addAsteroidsFrequently();
}