#pragma once
#include "Entity.h"
#include <vector>
#include <array>

using namespace std;

class Manager {
private:
	array<vector<Entity*>, maxGroupId> entsByGroup;
	array<Entity*, maxHandlerId> handlers;

public: 
	Manager();
	virtual ~Manager();

	void refresh();
	void update();
	void render();

	Entity* addEntity(grpId_type gId = _grp_GENERAL);

	const auto& getEntities(grpId_type gId = _grp_GENERAL) {
		return entsByGroup[gId];
	}

	inline void setHandler(hdlrId_type hId, Entity* e) {
		handlers[hId] = e;
	}

	inline Entity* getHandler(hdlrId_type hId) {
		return handlers[hId];
	}
};