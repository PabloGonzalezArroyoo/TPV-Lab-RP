#pragma once
#include "../utils/Constants.h"
using namespace std;

// COMPONENTES
using cmpId_type = unsigned int;

enum cmpId : cmpId_type {
	_TRANSFORM,
	_FIGHTERCTRL,
	_HEALTH,
	_DEACCELERATION,
	_GUN,
	_SHOWATOPPOSITESIDE,
	_FRAMED_IMAGE,
	_GENERATIONS,
	_FOLLOW,
	_DISABLE_ON_EXIT,
	_BUTTON,

	//DO NOT REMOVE THIS
	_LAST_CMP_ID
};

constexpr cmpId_type maxComponentId = _LAST_CMP_ID;

// GRUPOS
using grpId_type = unsigned int;

enum grpId : grpId_type {
	_grp_GENERAL,
	_grp_ASTEROIDS,
	_grp_BULLETS,
	_grp_UI,

	//DO NOT REMOVE THIS
	_LAST_GRP_ID
};

constexpr grpId_type maxGroupId = _LAST_GRP_ID;

// HANDLER
using hdlrId_type = unsigned int;

enum hdlrId : hdlrId_type {
	_hdlr_FIGHTER,

	//DO NOT REMOVE THIS
	_LAST_HDLR_ID
};

constexpr hdlrId_type maxHandlerId = _LAST_HDLR_ID;

// MESSAGES
class Entity;
using msgId_type = unsigned int;
enum msgId : msgId_type {
	_m_PLAYER_DIED, //
	_m_ASTEROID_COLLIDED,
	_m_CREATE_BULLET
};

struct Message {
	msgId_type id;
	// _m_STAR_EATEN
	struct {
		Entity* e;
	} player_died_data;
	// _m_ADD_STARS
	struct {
		unsigned int n;
	} asteroid_collided_data;
	struct {
		Entity* pl;
	} create_bullet_data;
};


// SYSTEMS

using sysId_type = unsigned int;

enum sysId : sysId_type {
	_sys_GAME_CTRL,
	_sys_ASTEROIDS,
	_sys_BULLET,
	_sys_FIGHTER,
	_sys_COLLISION,
	_sys_RENDER,

	//DO NOT REMOVE THIS
	_LAST_SYS_ID
};

constexpr sysId_type maxSystemId = _LAST_SYS_ID;

enum WINNER {
	NONE_WIN, ASTEROIDS_WIN, FIGHTER_WIN
};

enum STATE {
	MAINMENU_STATE, PLAY_STATE, PAUSE_STATE, GAMEOVER_STATE, WIN_STATE
};