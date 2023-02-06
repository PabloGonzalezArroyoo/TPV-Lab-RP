#pragma once

using cmpId_type = unsigned int;

enum cmpId : cmpId_type {
	_TRANSFORM = 0,
	_IMAGE,
	_FIGHTERCTRL,
	_HEALTH,
	_DEACCELERATION,
	_GUN,
	_SHOWATOPPOSITESIDE,
	_FRAMEDIMAGE,
	_GENERATIONS,
	_FOLLOW,
	_DISABLEONEXIT,

	// do not remove this
	_LAST_CMP_ID
};

constexpr cmpId_type maxComponentId = _LAST_CMP_ID;