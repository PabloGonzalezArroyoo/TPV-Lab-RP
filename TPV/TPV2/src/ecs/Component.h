#pragma once
#include "../game/ecs_def.h"

using namespace std;

// Para evitar la dependencia circular
class Manager;
class Entity;

class Component {
protected:
	// Referencia a mi entidad y a mi manager
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

	// Métodos virtuales
	virtual void initComponent() { };
	virtual void update() { };
	virtual void render() { };
	virtual void handleInput() { };
};