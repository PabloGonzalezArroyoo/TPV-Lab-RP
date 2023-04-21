#include "GameCtrlSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"
#include "../game/PauseState.h"
#include "../game/PlayState.h"
#include "../game/GameOverState.h"
#include "../game/MainMenuState.h"
#include "../game/WinState.h"
#include "../game/MultiPlayerState.h"

// Recibir mensajes
void GameCtrlSystem::receive(const Message& m) {

	Message mes;
	switch (m.id) {
		// Inicializar estado -> guardar estado, game y componente si es el estado de pausa
		case _m_INIT_STATE: 
			state = m._state_data.st;
			game = m._state_data.g;
			if (state == PAUSE_STATE) mngr->getComponent<Health>(mngr->getHandler(_hdlr_FIGHTER))->setLives(m._state_data.l);
			break;
		
		// Daño del jugador
		case _m_PLAYER_DAMAGED:
			onCollision_FighterAsteroid();
			break;

		// Al pulsar espacio, reproducir sonido y lanzar X estado según en el que me encuentre
		case _m_SPACEBAR_PRESSED:
			mes.id = _m_PLAY_SOUND;
			mes._sound_data.sound = &sdlutils().soundEffects().at(SELECT);
			mngr->send(mes);

			if (state == MAINMENU_STATE) game->getStateMachine()->pushState(new PlayState(game));
			else if (state == GAMEOVER_STATE || state == WIN_STATE) game->getStateMachine()->pushState(new MainMenuState(game));
			else if (state == PAUSE_STATE) game->getStateMachine()->popState();
			break;

		// Al pulsar espacio, salir o cortar flujo dependiendo del estado
		case _m_ESC_PRESSED:
			if (state == PLAY_STATE) 
				game->getStateMachine()->pushState(new PauseState(game, mngr->getComponent<Health>(mngr->getHandler(_hdlr_FIGHTER))->getLifes()));
			else game->changeControl();
			break;

		case _m_M_PRESSED:
			game->getStateMachine()->changeState(new MultiPlayerState()); break;

		// Al ganar
		case _m_PLAYER_WINS:
			onAsteroidsExtinction();
			break;
	}
}

void GameCtrlSystem::initSystem() {
	auto network = mngr->getSystem<NetworkSystem>();

	if (!network) {
		// Crea la nave y le añade los componentes basicos
		Entity* f = mngr->addEntity();

		mngr->addComponent<Transform>(f, PLAYER_INITIAL_POS, PLAYER_WIDTH, PLAYER_HEIGHT);
		mngr->addComponent<Health>(f);

		// Setea el handler de la nave
		mngr->setHandler(_hdlr_FIGHTER, f);
	}
	else {
		// Crea la nave y le añade los componentes basicos
		Entity * good = mngr->addEntity();
		Entity* bad = mngr->addEntity(_grp_MULTIPLAYER);

		Vector2D host = Vector2D(0, WIN_HEIGHT / 2 - PLAYER_HEIGHT / 2);
		Vector2D client = Vector2D(WIN_WIDTH - PLAYER_WIDTH, WIN_HEIGHT / 2 - PLAYER_HEIGHT / 2);

		if (network->isHost()) {
			mngr->addComponent<Transform>(good, host, PLAYER_WIDTH, PLAYER_HEIGHT, Vector2D(), 90);
			mngr->addComponent<Transform>(bad, client, PLAYER_WIDTH, PLAYER_HEIGHT, Vector2D(), -90);
		}
		else {
			mngr->addComponent<Transform>(bad, host, PLAYER_WIDTH, PLAYER_HEIGHT, Vector2D(), 90);
			mngr->addComponent<Transform>(good, client, PLAYER_WIDTH, PLAYER_HEIGHT, Vector2D(), -90);
		}


		// Crea la nave y le añade los componentes basicos
		mngr->addComponent<Health>(good);
		mngr->addComponent<Health>(bad);

		// Setea el handler de la nave
		mngr->setHandler(_hdlr_FIGHTER, good);
		mngr->setHandler(_hdlr_GHOST_FIGHTER, bad);
	}

}

// Al desaparecer todos los asteroides
void GameCtrlSystem::onAsteroidsExtinction() {
	// Si se eliminan todos los asteroides se lanza el mensaje de parar la musica
	Message m;
	m.id = _m_STOP_MUSIC;
	m._music_data.music = &sdlutils().musics().at(GALAXY);
	mngr->send(m);

	// Lanzar estado de victoria
	game->getStateMachine()->changeState(new WinState(game));
}

// Si ha colisionado un asteroide con él
void GameCtrlSystem::onCollision_FighterAsteroid() {
	// Coger componente de vidas y reducir su contador
	Health* h = mngr->getComponent<Health>(mngr->getHandler(_hdlr_FIGHTER));
	h->setLives(h->getLifes() - 1);

	// Si aun tengo vidas, lanzar mensaje de que se ha acabado la ronda y estado de pausa
	if (h->getLifes() > 0) {
		Message m;
		m.id = _m_ROUND_OVER;
		mngr->send(m);

		game->getStateMachine()->pushState(new PauseState(game, h->getLifes()));
	}
	// Si no, parar música y lanzar el estado de GameOver
	else {
		Message m;
		m.id = _m_STOP_MUSIC;
		m._music_data.music = &sdlutils().musics().at(GALAXY);
		mngr->send(m);
		
		game->getStateMachine()->changeState(new GameOverState(game));
	}
}