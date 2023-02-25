#pragma once
#include "Entity.h"
#include <vector>

using namespace std;

class Manager {
public:
	Manager();
	virtual ~Manager();

	void refresh();
	void update();
	void render();

	//virtual Entity* getPlayer() { };

	Entity* addEntity();

private:
	vector<Entity*> ents_;
};