#include "PlayState.h"
#include "Game.h"
#include "GameOverState.h"
#include "PauseState.h"
#include "../sdlutils/SDLUtils.h"

// Constructora
PlayState::PlayState(Game* g) : GameState(g) {
	// Fondo azul
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 123, 123, 1);

	// Creamos el manager del estado
	mng = new Manager();

	// Reproducimos la música de fondo	
	// game->getMusic(GALAXY)->play();

	// Añadimos al jugador con todos sus componentes
	auto player = mng->addEntity();
	player->addComponent<Transform>(PLAYER_INITIAL_POS, Vector2D(), PLAYER_WIDTH, PLAYER_HEIGHT);
	player->addComponent<Image>(g->getTexture(FIGTHER));
	player->addComponent<FighterCtrl>(g, g->getSound(THRUST));
	player->addComponent<DeAcceleration>();
	player->addComponent<ShowAtOppositeSide>();
	player->addComponent<Gun>(g, g->getSound(FIRESFX));
	player->addComponent<Health>(g->getTexture(HEALTH));

	// Configuramos el handler del jugador
	mng->setHandler(_hdlr_FIGHTER, player);

	//Creamos el controlador de asteroides y añadimos 10 al juego
	astController = new AsteroidsController(mng, game);
	astController->createAsteroids(10);
}

// Llamamos al update del padre (que llama al del manager), 
// comprobamos las colisiones en el juego y si aún no acaba llamamos a la creacion de asteroides
void PlayState::update() {
	GameState::update();
	astController->addAsteroidsFrequently();
	checkCollisions();
}

// Comprobar si los asteroides colisionan con las balas o el jugador
void PlayState::checkCollisions() {
	// Cogemos los grupos
	auto asts = mng->getEntities(_grp_ASTEROIDS);
	auto bullets = mng->getEntities(_grp_BULLETS);
	Entity* player = mng->getHandler(_hdlr_FIGHTER);
	// Guardamos componentes necesarios
	Transform* plTr = player->getComponent<Transform>();
	Transform* astTr = nullptr;
	Transform* blltTr = nullptr;

	// Nos guardamos el estado del jugador (vivo o no)
	bool plCollided = !player->isAlive();

	// Recorremos el grupo de asteroides mientras el jugador no haya colisionado
	for (auto it = asts.begin(); it != asts.end() && !plCollided; it++) {
		// Si el asteroide que tengo que comprobar sigue vivo
		if ((*it)->isAlive()) {
			// Me guardo su componente transform
			astTr = (*it)->getComponent<Transform>();

			// Comprobar colisión con el jugador
			plCollided = Collisions::collidesWithRotation(
				plTr->getPosition(), plTr->getWidth(), plTr->getHeight(), plTr->getRotation(),
				astTr->getPosition(), astTr->getWidth(), astTr->getHeight(), astTr->getRotation());

			// Si el asteroide no colisiona con el jugador, compruebo las balas
			if (!plCollided) {
				// Recorro las balas 
				for (auto itB = bullets.begin(); itB != bullets.end(); itB++) {
					// Si la bala a comprobar sigue viva
					if ((*itB)->isAlive()) {
						// Me guardo el componente transform de la bala
						blltTr = (*itB)->getComponent<Transform>();

						// Comprobar colisión con la bala
						bool bllCollided = Collisions::collidesWithRotation(
							blltTr->getPosition(), blltTr->getWidth(), blltTr->getHeight(), blltTr->getRotation(),
							astTr->getPosition(), astTr->getWidth(), astTr->getHeight(), astTr->getRotation());
						
						// Si colisiona con la bala
						if (bllCollided) collisionAsteroidBullet(*it, *itB);
					}
				}
			}
			// Si el asteroide colisiona con el jugador
			else plCollided = collisionAsteroidPlayer(player);
		}		
	}
}


// Cuando el jugador recibe daño
void PlayState::OnPlayerDamage(Entity* pl) {
	// Coger transform del player y colocarno en su estado incial
	Transform* plTr = pl->getComponent<Transform>();
	plTr->setPosition(PLAYER_INITIAL_POS);
	plTr->setVelocity(Vector2D());
	plTr->setRotation(0);
	pl->getComponent<FighterCtrl>()->setRot(0);

	// Crear de nuevo los asteroides
	astController->createAsteroids(10);

	// Cambiar al estado de pausa
	game->getStateMachine()->pushState(new PauseState(game, pl->getComponent<Health>()->checkLifes()));
}

// Cargar el estado de gameOver al morir
void PlayState::OnPlayerDies() {
	game->getStateMachine()->changeState(new GameOverState(game));
}

// Colisión del asteroide con el jugador
bool PlayState::collisionAsteroidPlayer(Entity* player) {
	// Reproducir sonido de muerte
	game->getSound(OOF)->play();

	// Destruir los asteroides y marcar la colisión
	astController->destroyAllAsteroids();

	// Actualizar vidas y añadir un retardo
	auto health = player->getComponent<Health>();
	health->removeLife();
	SDL_Delay(1000);

	// Comprobar según el nº de vidas si el jugador debe morir o solo recibir daño
	if (health->checkLifes() <= 0) OnPlayerDies();
	else OnPlayerDamage(player);

	// Confirmar colisión
	return true;
}

// Colisión del asteroide con la bala
void PlayState::collisionAsteroidBullet(Entity* asteroid, Entity* bullet) {
	// Reproducir sonido de explosión
	game->getSound(EXPLOSION)->play();

	// Procesar destrucción del asteroide
	astController->OnCollision(asteroid);

	// Desactivar bala
	bullet->setAlive(false);
}