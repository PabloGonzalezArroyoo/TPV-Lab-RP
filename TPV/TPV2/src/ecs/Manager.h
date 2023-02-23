#pragma once
#include "Entity.h"
#include <vector>

using namespace std;

class Manager {
private:
	vector<Entity*> gObjs;

public: 
	Manager();
	virtual ~Manager();

	void refresh();
	void update();
	void render();

	Entity* addEntity();
};