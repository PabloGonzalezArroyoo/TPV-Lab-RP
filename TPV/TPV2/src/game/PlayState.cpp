#include "PlayState.h"
#include "Game.h"
#include "GameOverState.h"
#include "PauseState.h"

PlayState::PlayState(Game* g) : GameState(g), gameOver(false) {
	// game->getSound(DOOM)->play();
	mng = new Manager();
	auto player = mng->addEntity();
	player->addComponent<Transform>(PLAYER_INITIAL_POS, Vector2D(), PLAYER_WIDTH, PLAYER_HEIGHT);
	player->addComponent<Image>(g->getTexture(FIGTHER));
	player->addComponent<FighterCtrl>(g, g->getSound(THRUST));
	player->addComponent<DeAcceleration>();
	player->addComponent<ShowAtOppositeSide>();
	player->addComponent<Gun>(g, g->getSound(FIRESFX));
	player->addComponent<Health>(g->getTexture(HEALTH));

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
	if (!gameOver) astController->addAsteroidsFrequently();
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

	// Comienza la fiesta
	bool plCollided = !player->isAlive();
	for (auto it = asts.begin(); it != asts.end() && !plCollided; it++) {
		if ((*it)->isAlive()) {
			astTr = (*it)->getComponent<Transform>();
			plCollided = Collisions::collidesWithRotation(
				plTr->getPosition(), plTr->getWidth(), plTr->getHeight(), plTr->getRotation(),
				astTr->getPosition(), astTr->getWidth(), astTr->getHeight(), astTr->getRotation());
			
			if (!plCollided) {
				for (auto itB = bullets.begin(); itB != bullets.end(); itB++) {
					if ((*itB)->isAlive()) {
						blltTr = (*itB)->getComponent<Transform>();
						bool astCollided = Collisions::collidesWithRotation(
							blltTr->getPosition(), blltTr->getWidth(), blltTr->getHeight(), blltTr->getRotation(),
							astTr->getPosition(), astTr->getWidth(), astTr->getHeight(), astTr->getRotation());
						if (astCollided) {
							game->getSound(EXPLOSION)->play();
							astController->OnCollision(*it);
							(*itB)->setAlive(false);
						}
					}
				}
			}
			else {
				game->getSound(OOF)->play();
				astController->destroyAllAsteroids();
				plCollided = true;
				auto health = player->getComponent<Health>();
				health->removeLife();
				SDL_Delay(1000);
				if (health->checkLifes() <= 0) OnPlayerDies();
				else OnPlayerDamage(player);
			}
		}		
	}
}

void PlayState::OnPlayerDamage(Entity* pl) {
	Transform* plTr = pl->getComponent<Transform>();
	plTr->setPosition(PLAYER_INITIAL_POS);
	plTr->setVelocity(Vector2D());
	plTr->setRotation(0);
	astController->createAsteroids(10);
	pl->getComponent<FighterCtrl>()->setRot(0);
	game->getStateMachine()->pushState(new PauseState(game, pl->getComponent<Health>()->checkLifes()));
}

void PlayState::OnPlayerDies() {
	gameOver = true;
	game->getStateMachine()->changeState(new GameOverState(game));
}