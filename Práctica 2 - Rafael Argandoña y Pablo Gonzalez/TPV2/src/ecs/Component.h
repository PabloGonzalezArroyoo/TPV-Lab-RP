#pragma once
#include "../game/ecs_def.h"

using namespace std;

// Para evitar la dependencia circular
class Manager;
class Entity;

struct Component {
protected:
	Entity* ent;
	Manager* mngr;

public:
	Component() : ent(), mngr() { }
	virtual ~Component() { }
	inline void setContext(Entity* _ent, Manager* _mngr) {
		ent = _ent;
		mngr = _mngr;
	}
	virtual void initComponent() { }
};