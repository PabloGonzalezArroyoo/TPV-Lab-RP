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
	checkCollisions();
	astController->addAsteroidsFrequently();
}

void PlayState::checkCollisions() {
	// Cogemos los grupos
	auto asts = mng->getEntities(_grp_ASTEROIDS);
	auto bullets = mng->getEntities(_grp_BULLETS);
	Entity* player = mng->getHandler(_hdlr_FIGHTER);
	// Guardamos componentes necesarios
	Transform* plTr = player->getComponent<Transform>();
	Transform* astTr = nullptr;
	Transform* blltTr = nullptr;

	bool plCollided = player->isAlive();
	for (auto it = asts.begin(); it != asts.end() && plCollided; it++) {
		if ((*it)->isAlive()) {
			astTr = (*it)->getComponent<Transform>();
			plCollided = Collisions::collidesWithRotation(
				plTr->getPosition(), plTr->getWidth(), plTr->getHeight(), plTr->getRotation(),
				astTr->getPosition(), astTr->getWidth(), astTr->getHeight(), astTr->getRotation());

			if (!plCollided) {
				for (auto itB = bullets.begin(); itB != asts.end(); itB++) {
					if ((*itB)->isAlive()) {
						blltTr = (*itB)->getComponent<Transform>();
						bool astCollided = Collisions::collidesWithRotation(
							blltTr->getPosition(), blltTr->getWidth(), blltTr->getHeight(), blltTr->getRotation(),
							astTr->getPosition(), astTr->getWidth(), astTr->getHeight(), astTr->getRotation());
						if (astCollided) {
							(*it)->setAlive(false);
							(*itB)->setAlive(false);
						}
					}
				}
			}
			else {
				player->setAlive(false);
				(*it)->setAlive(false);
				plCollided = true;
			}
		}		
	}
}