#pragma once

using namespace std;

using cmpId_type = unsigned int;

enum cmpId : cmpId_type {
	_TRANSFORM,
	_IMAGE,
	_FIGHTERCTRL,
	_HEALTH,
	_DEACCELERATION,
	_GUN,
	_SHOWATOPPOSITESIDE,
	_FRAMED_IMAGE,
	_GENERATIONS,
	_FOLLOW,
	_DISABLE_ON_EXIT,


	//DO NOT REMOVE THIS
	_LAST_CMP_ID
};

constexpr cmpId_type maxComponentId = _LAST_CMP_ID;