#include "Manager.h"
#include <iostream>

Manager::Manager() : entsByGroup() {
	for (auto& groupEntities : entsByGroup) {
		groupEntities.reserve(100);
	}
}

Manager::~Manager() {
	for (int i = 0; i < maxGroupId; i++) {
		for (auto g : entsByGroup[i]) delete g;
	}
}

Entity* Manager::addEntity(grpId_type gId) {
	Entity* g = new Entity();
	g->setAlive(true);
	g->setContext(this);
	entsByGroup[gId].push_back(g);
	return g;
}

void Manager::refresh() {
	for (grpId_type gId = 0; gId < maxGroupId; gId++) {
		auto& grpEnts = entsByGroup[gId];
		grpEnts.erase(
			remove_if(grpEnts.begin(), grpEnts.end(),
				[](Entity* g) {
					if (g->isAlive()) return false;
					else { delete g; return true; }
				}), grpEnts.end()
			);
	}
}

void Manager::update() {
	for (auto& ents : entsByGroup) {
		auto n = ents.size();
		for (auto i = 0u; i < n; i++) ents[i]->update();
	}
}

void Manager::render() {
	for (auto& ents : entsByGroup) {
		auto n = ents.size();
		for (auto i = 0u; i < n; i++) ents[i]->render();
	}
}