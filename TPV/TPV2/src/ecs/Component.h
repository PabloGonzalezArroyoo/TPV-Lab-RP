#pragma once

class Entity;
class Manager;

class Component {
protected:
	Entity* myObj;
	Manager* myMng;

public:
	Component(): myObj(nullptr), myMng(nullptr) { }
	virtual ~Component() { }

	inline void setContext(Entity* _obj, Manager* _mng) {
		myObj = _obj;
		myMng = _mng;
	}

	virtual void initComponent();
	virtual void update();
	virtual void render();
	virtual void handleInput();
};