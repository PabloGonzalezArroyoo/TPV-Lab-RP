#pragma once
#include "../sdlutils/SDLUtils.h"
#include "../game/ecs_def.h"
class Manager;

class System {
public:
	virtual ~System() { }
	void setContext(Manager* _mngr) {
		mngr = _mngr;
	}
	virtual void initSystem() { }
	virtual void update() { }
	virtual void receive(const Message& m) { }

protected:
	Manager* mngr;
};