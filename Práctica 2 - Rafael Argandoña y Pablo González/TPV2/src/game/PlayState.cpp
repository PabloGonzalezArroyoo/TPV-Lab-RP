#include "PlayState.h"
#include "Game.h"
#include "GameOverState.h"
#include "PauseState.h"
#include "../sdlutils/SDLUtils.h"
#include "../systems/RenderSystem.h"
#include "../systems/FighterSystem.h"
#include "../systems/BulletSystem.h"
#include "../systems/AsteroidsSystem.h"
#include "../systems/CollisionsSystem.h"

// Constructora
PlayState::PlayState(Game* g) : GameState(g) {
	// Fondo azul
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 123, 123, 1);

	// Creamos el manager del estado
	mng = new Manager();

	// Reproducimos la música de fondo	
	sdlutils().musics().at(GALAXY).play();

	// Sistemas
	mng->addSystem<FighterSystem>();
	mng->addSystem<AsteroidsSystem>();
	mng->addSystem<BulletSystem>();
	mng->addSystem<CollisionsSystem>();
	mng->addSystem<RenderSystem>();

	//// Añadimos al jugador con todos sus componentes
	//auto player = mng->addEntity();
	//player->addComponent<Transform>(PLAYER_INITIAL_POS, Vector2D(), PLAYER_WIDTH, PLAYER_HEIGHT);
	//player->addComponent<Image>(&sdlutils().images().at(FIGHTER));
	//player->addComponent<FighterCtrl>(g, &sdlutils().soundEffects().at(THRUST));
	//player->addComponent<DeAcceleration>();
	//player->addComponent<ShowAtOppositeSide>();
	//player->addComponent<Gun>(g, &sdlutils().soundEffects().at(FIRESFX));
	//player->addComponent<Health>(&sdlutils().images().at(HEART));

	//// Configuramos el handler del jugador
	//mng->setHandler(_hdlr_FIGHTER, player);

	////Creamos el controlador de asteroides y añadimos 10 al juego
	//astController = new AsteroidsController(mng, game);
	//astController->createAsteroids(10);
}

// Llamamos al update del padre (que llama al del manager), 
// comprobamos las colisiones en el juego y si aún no acaba llamamos a la creacion de asteroides
void PlayState::update() {
	GameState::update();
	checkCollisions();
}

// Comprobar si los asteroides colisionan con las balas o el jugador
void PlayState::checkCollisions() {
	//// Cogemos los grupos
	//auto asts = mng->getEntities(_grp_ASTEROIDS);
	//Entity* player = mng->getHandler(_hdlr_FIGHTER);
	//// Guardamos componentes necesarios
	//Transform* plTr = player->getComponent<Transform>();
	//Transform* astTr = nullptr;

	//// Nos guardamos el estado del jugador (vivo o no)
	//bool plCollided = !player->isAlive();
	//bool blltCollided = false;

	//// Recorremos el grupo de asteroides mientras el jugador no haya colisionado
	//for (auto it = asts.begin(); it != asts.end() && !plCollided; it++) {
	//	// Si el asteroide que tengo que comprobar sigue vivo
	//	if ((*it)->isAlive()) {
	//		// Me guardo su componente transform
	//		astTr = (*it)->getComponent<Transform>();
	//		plCollided = collisionAsteroidPlayer(player, astTr);

	//		// Si el asteroide no ha chocado con el jugador, compruebo con las balas
	//		if (!plCollided) {
	//			// Llamo al método de la comprobacion y me guardo la información
	//			blltCollided = collisionAsteroidBullet(astTr);
	//			// Si el asteroide colisiona con la bala desactivo la bala
	//			if (blltCollided) astController->OnCollision((*it));
	//		}
	//	}		
	//}
}


// Cuando el jugador recibe daño
void PlayState::OnPlayerDamage(Entity* pl) {
	//// Coger transform del player y colocarno en su estado incial
	//Transform* plTr = pl->getComponent<Transform>();
	//plTr->setPosition(PLAYER_INITIAL_POS);
	//plTr->setVelocity(Vector2D());
	//plTr->setRotation(0);
	//pl->getComponent<FighterCtrl>()->setRot(0);

	//// Crear de nuevo los asteroides
	//astController->createAsteroids(10);

	//// Cambiar al estado de pausa
	//game->getStateMachine()->pushState(new PauseState(game, pl->getComponent<Health>()->checkLifes()));
}

// Cargar el estado de gameOver al morir
void PlayState::OnPlayerDies() {
	sdlutils().musics().at(GALAXY).haltMusic();
	game->getStateMachine()->changeState(new GameOverState(game));
}

//// Colisión del asteroide con el jugador
//bool PlayState::collisionAsteroidPlayer(Entity* player, Transform* astTr) {
//	//// Nos guardamos el estado del jugador (vivo o no)
//	//bool collision = !player->isAlive();
//	//Transform* plTr = player->getComponent<Transform>();
//
//	//// Comprobar colisión con el jugador
//	//collision = Collisions::collidesWithRotation(
//	//	plTr->getPosition(), plTr->getWidth(), plTr->getHeight(), plTr->getRotation(),
//	//	astTr->getPosition(), astTr->getWidth(), astTr->getHeight(), astTr->getRotation());
//
//	//if (collision) {
//	//	// Reproducir sonido de muerte
//	//	sdlutils().soundEffects().at(OOF).play();
//
//	//	// Destruir los asteroides y las balas
//	//	astController->destroyAllAsteroids();
//	//	mng->removeEntities(_grp_BULLETS);
//
//	//	// Actualizar vidas y añadir un retardo
//	//	auto health = player->getComponent<Health>();
//	//	health->removeLife();
//	//	SDL_Delay(1000);
//
//	//	// Comprobar según el nº de vidas si el jugador debe morir o solo recibir daño
//	//	if (health->checkLifes() <= 0) OnPlayerDies();
//	//	else OnPlayerDamage(player);
//
//	//	// Confirmar colisión
//	//	return true;
//	//}
//	//return false;
//}

// Colisión del asteroide con la bala
//bool PlayState::collisionAsteroidBullet(Transform* astTr) {
//	//bool collision = false;
//	//auto bullets = mng->getEntities(_grp_BULLETS);
//	//Transform* blltTr = nullptr;
//
//	////Recorro las balas 
//	//for (auto itB = bullets.begin(); itB != bullets.end() && !collision; itB++) {
//	//	// Si la bala a comprobar sigue viva
//	//	if ((*itB)->isAlive()) {
//	//		// Me guardo el componente transform de la bala
//	//		blltTr = (*itB)->getComponent<Transform>();
//
//	//		// Comprobar colisión con la bala
//	//		collision = Collisions::collidesWithRotation(
//	//			blltTr->getPosition(), blltTr->getWidth(), blltTr->getHeight(), blltTr->getRotation(),
//	//			astTr->getPosition(), astTr->getWidth(), astTr->getHeight(), astTr->getRotation());
//
//	//		if (collision) {
//	//			// Reproducir sonido de explosión
//	//			sdlutils().soundEffects().at(EXPLOSION).play();
//	//			// Desactivar bala
//	//			(*itB)->setAlive(false);
//	//		}
//	//	}
//	//}
//	//return collision;
//}