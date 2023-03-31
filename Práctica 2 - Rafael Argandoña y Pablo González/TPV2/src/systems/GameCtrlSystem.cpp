
#include "GameCtrlSystem.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"
#include "../game/PauseState.h"
#include "../game/PlayState.h"
#include "../game/GameOverState.h"
#include "../game/MainMenuState.h"
#include "../game/WinState.h"

void GameCtrlSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_INIT_STATE: 
			state = m._state_data.st;
			game = m._state_data.g;
			if (state == PAUSE_STATE) mngr->getComponent<Health>(mngr->getHandler(_hdlr_FIGHTER))->setLives(m._state_data.l);
			break;
		
		case _m_PLAYER_DAMAGED:
			onCollision_FighterAsteroid();
			break;

		case _m_SPACEBAR_PRESSED:
			if (state == MAINMENU_STATE) game->getStateMachine()->pushState(new PlayState(game));
			else if (state == GAMEOVER_STATE || state == WIN_STATE) game->getStateMachine()->pushState(new MainMenuState(game));
			else if (state == PAUSE_STATE) game->getStateMachine()->popState();

			Message m;
			m.id = _m_PLAY_SOUND;
			m._sound_data.sound = &sdlutils().soundEffects().at(SELECT);
			mngr->send(m);
			break;

		case _m_ESC_PRESSED:
			if (state == PLAY_STATE) 
				game->getStateMachine()->pushState(new PauseState(game, mngr->getComponent<Health>(mngr->getHandler(_hdlr_FIGHTER))->getLifes()));
			else game->changeControl();
			break;

		case _m_PLAYER_WINS:
			onAsteroidsExtinction();
			break;
	}
}

void GameCtrlSystem::initSystem() {
	Entity* f = mngr->addEntity();

	mngr->addComponent<Transform>(f, PLAYER_INITIAL_POS, PLAYER_WIDTH, PLAYER_HEIGHT);
	mngr->addComponent<Health>(f);

	mngr->setHandler(_hdlr_FIGHTER, f);
}

void GameCtrlSystem::update() { }

void GameCtrlSystem::onAsteroidsExtinction() {
	Message m;
	m.id = _m_STOP_MUSIC;
	m._music_data.music = &sdlutils().musics().at(GALAXY);
	mngr->send(m);

	game->getStateMachine()->changeState(new WinState(game));
}

void GameCtrlSystem::onCollision_FighterAsteroid() {
	Health* h = mngr->getComponent<Health>(mngr->getHandler(_hdlr_FIGHTER));
	h->setLives(h->getLifes() - 1);

	if (h->getLifes() > 0) {
		// LANZAR EL MENSAJE DE QUE ACABO LA RONDA
		Message m;
		m.id = _m_ROUND_OVER;
		mngr->send(m);

		// LANZAS LA PAUSA
		game->getStateMachine()->pushState(new PauseState(game, h->getLifes()));
	}

	else {
		// LANZAR estado de derrota
		Message m;
		m.id = _m_STOP_MUSIC;
		m._music_data.music = &sdlutils().musics().at(GALAXY);
		mngr->send(m);

		game->getStateMachine()->changeState(new GameOverState(game));
	}
}