#include "Manager.h"

Manager::Manager() : gObjs() {
	gObjs.reserve(100);
}

Manager::~Manager() {
	for (auto g : gObjs) delete g;
}

Entity* Manager::addEntity() {
	Entity* g = new Entity();
	g->setAlive(true);
	g->setContext(this);
	gObjs.push_back(g);
	return g;
}

void Manager::refresh() {
	gObjs.erase(
		remove_if(gObjs.begin(), gObjs.end(), [](Entity* g) {
			if (g->isAlive()) return false;
			else { delete g; return true; }
		}), gObjs.end()
	);
}

void Manager::update() {
	auto n = gObjs.size();
	for (auto i = 0u; i < n; i++) gObjs[i]->update();
}

void Manager::render() {
	auto n = gObjs.size();
	for (auto i = 0u; i < n; i++) gObjs[i]->render();
}