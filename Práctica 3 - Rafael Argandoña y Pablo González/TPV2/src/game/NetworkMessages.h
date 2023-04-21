#pragma once
#include "../sdlutils/SDLNetUtils.h"

enum nwId : Uint8 {
	_nw_REQUEST_CONNECTION,
	_nw_OTHER_PLAYER_VEL,
	_nw_OTHER_PLAYER_ROT,
	_nw_OTHER_PLAYER_SHOT,
};

struct NetworkMessage {
	Uint8 id;
	
	_IMPL_SERIALIAZION_(id);
};


// MENSAJES DE PETICION DE CONEXION
struct RequestConection : NetworkMessage {
	char name[11];

	_IMPL_SERIALIAZION_WITH_BASE_(NetworkMessage, name);
};

// MENSAJE DE VELOCIDAD DE LA NAVE DEL OTRO PLAYER
struct OtherVelocity : NetworkMessage {
	float x;
	float y;

	_IMPL_SERIALIAZION_WITH_BASE_(NetworkMessage, x, y);
};

// MENSAJE DE ROTACION DE LA NAVE DEL OTRO PLAYER
struct OtherRotation : NetworkMessage {
	float r;

	_IMPL_SERIALIAZION_WITH_BASE_(NetworkMessage, r);
};

// PARAMETROS BALA DE OTRO PLAYER
struct OtherBullet : NetworkMessage {
	float x;
	float y;
	float rot;

	_IMPL_SERIALIAZION_WITH_BASE_(NetworkMessage, x, y, rot);
};