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
#include "../systems/GameCtrlSystem.h"

// Constructora
PlayState::PlayState(Game* g) : GameState(g) {
	// Fondo azul
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 123, 123, 1);

	// Creamos el manager del estado
	mng = new Manager();

	// Reproducimos la música de fondo	
	sdlutils().musics().at(GALAXY).play();

	// Sistemas
	mng->addSystem<GameCtrlSystem>();
	mng->addSystem<FighterSystem>();
	mng->addSystem<AsteroidsSystem>();
	mng->addSystem<BulletSystem>();
	mng->addSystem<CollisionsSystem>();
	mng->addSystem<RenderSystem>();

	Message m;
	m.id = _m_INIT_STATE;
	m._state_data.st = PLAY_STATE;
	m._state_data.g = g;
	mng->send(m);
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