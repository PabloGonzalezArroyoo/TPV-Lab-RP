#include "Manager.h"
#include <iostream>

Manager::Manager() : entsByGroup(), sys(), handlers() {
	for (auto& groupEntities : entsByGroup) {
		groupEntities.reserve(100);
	}
}

Manager::~Manager() {
	for (int i = 0; i < maxGroupId; i++) {
		for (auto g : entsByGroup[i]) delete g;
	}

	for (int i = 0; i < maxSystemId; i++) {
		delete sys[i];
		sys[i] = nullptr;
	}
}

Entity* Manager::addEntity(grpId_type gId) {
	Entity* g = new Entity(gId);
	g->alive = true;
	entsByGroup[gId].push_back(g);
	return g;
}

void Manager::refresh() {
	for (grpId_type gId = 0; gId < maxGroupId; gId++) {
		auto& grpEnts = entsByGroup[gId];
		grpEnts.erase(
			remove_if(grpEnts.begin(), grpEnts.end(),
				[](Entity* g) {
					if (g->alive) return false;
					else { delete g; return true; }
				}), grpEnts.end()
			);
	}
}

void Manager::update() {
	for (System* s : sys) {
		if (s != nullptr) s->update();
	}
}