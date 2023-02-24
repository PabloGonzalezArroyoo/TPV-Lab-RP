#pragma once
#include "../game/ecs_def.h"
#include "Entity.h"

class Manager;
class Entity;
class Component {
protected:
	Entity* myObj = nullptr;
	Manager* myMng;

public:
	// Constructora y destructora
	Component(): myObj(nullptr), myMng(nullptr) { }
	virtual ~Component() { }

	// Setters
	inline void setContext(Entity* _obj, Manager* _mng) {
		myObj = _obj;
		myMng = _mng;
	}

	// M�todos virtuales
	virtual void initComponent() {};
	virtual void update() {};
	virtual void render() {};
	virtual void handleInput() {};
};