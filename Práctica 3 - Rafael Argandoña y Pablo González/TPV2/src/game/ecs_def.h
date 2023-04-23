#pragma once
#include "../utils/Constants.h"
using namespace std;

// Los distintos estados del juego
enum STATE {
	MAINMENU_STATE, PLAY_STATE, MULTI_PLAYER, PAUSE_STATE, GAMEOVER_STATE, WIN_STATE
};

// COMPONENTES
using cmpId_type = unsigned int;

enum cmpId : cmpId_type {
	_TRANSFORM,
	_FIGHTERCTRL,
	_HEALTH,
	_FRAMED_IMAGE,
	_GENERATIONS,
	_FOLLOW,
	_TEXT,

	//DO NOT REMOVE THIS
	_LAST_CMP_ID
};

constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

// GRUPOS
using grpId_type = unsigned int;

enum grpId : grpId_type {
	_grp_GENERAL,
	_grp_MULTIPLAYER,
	_grp_ASTEROIDS,
	_grp_BULLETS,
	_grp_MULTIPLAYER_BULLETS,
	_grp_UI,
	_grp_TEXTS,


	//DO NOT REMOVE THIS
	_LAST_GRP_ID
};

constexpr grpId_type maxGroupId = _LAST_GRP_ID;

// HANDLER
using hdlrId_type = unsigned int;

enum hdlrId : hdlrId_type {
	_hdlr_FIGHTER,
	_hdlr_GHOST_FIGHTER,

	//DO NOT REMOVE THIS
	_LAST_HDLR_ID
};

constexpr hdlrId_type maxHandlerId = _LAST_HDLR_ID;

// MESSAGES
class Entity;
class Game;
class SoundEffect;
class Music;

using msgId_type = unsigned int;
enum msgId : msgId_type {
	_m_PLAYER_DAMAGED,
	_m_ROUND_OVER,
	_m_ASTEROID_COLLIDED,
	_m_CREATE_BULLET,
	_m_CREATED_BULLET,
	_m_PLAYER_WINS,
	_m_INIT_STATE,
	_m_SPACEBAR_PRESSED,
	_m_M_PRESSED,
	_m_ESC_PRESSED,
	_m_PLAY_SOUND,
	_m_PLAY_MUSIC,
	_m_STOP_MUSIC,

	_m_GHOST_MOVED,
	_m_GHOST_ROTATED,
	_m_GHOST_SHOT,
	_m_GHOST_DMG,
	_m_GHOST_HIT,
	_m_PAUSE_REQUEST
};

//En el mismo manager
struct Message {
	msgId_type id;
	// _m_PLAYER_DIED
	/*struct {
		grpId layer;
	} bullet_data;*/
	struct {
		Entity* e;
	} player_died_data;
	// _m_ASTEROIDS_COLLIDED
	struct {
		Entity* e;
	} asteroid_collided_data;
	// _m_PLAYER_DAMAGED
	struct {
		STATE st;
		Game* g;
		int l;
	} _state_data;
	struct {
		SoundEffect* sound;
	} _sound_data;
	struct {
		Music* music;
		int loop;
	} _music_data;
	struct {
		int sign;
	} my_data;
	struct {
		int sign;
		bool shot;
	} ghost_data;
};

// SYSTEMS
using sysId_type = unsigned int;

enum sysId : sysId_type {
	_sys_ASTEROIDS,
	_sys_BULLET,
	_sys_FIGHTER,
	_sys_GHOST_FIGHTER,
	_sys_COLLISIONS,
	_sys_RENDER,
	_sys_SOUND,
	_sys_NETWORK_,
	_sys_GAME_CTRL,

	//DO NOT REMOVE THIS
	_LAST_SYS_ID
};

constexpr sysId_type maxSystemId = _LAST_SYS_ID;

enum WINNER {
	NONE_WIN, ASTEROIDS_WIN, FIGHTER_WIN
};

