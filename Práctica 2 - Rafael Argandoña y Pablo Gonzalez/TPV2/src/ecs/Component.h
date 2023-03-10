#pragma once
#include "../game/ecs_def.h"

using namespace std;

// Para evitar la dependencia circular
class Manager;
class Entity;

struct Component {
protected:
	Entity* ent_;
	Manager* mngr_;

public:
	Component() : ent_(), mngr_() { }
	virtual ~Component() { }
	inline void setContext(Entity* ent, Manager* mngr) {
		ent_ = ent;
		mngr_ = mngr;
	}
	virtual void initComponent() { }
};