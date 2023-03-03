#pragma once
#include "Entity.h"
#include <vector>
#include <array>

using namespace std;

class Manager {
private:
	// Estructura de entidades -> array de vectores
	array<vector<Entity*>, maxGroupId> entsByGroup;
	array<Entity*, maxHandlerId> handlers;

public: 
	// Constructora y destructora
	Manager();
	virtual ~Manager();

	// Métodos esenciales
	void refresh();
	void update();
	void render();

	// Para añadir una entidad al manager
	Entity* addEntity(grpId_type gId = _grp_GENERAL);

	// Getters
	const auto& getEntities(grpId_type gId = _grp_GENERAL) {
		return entsByGroup[gId];
	}

	inline Entity* getHandler(hdlrId_type hId) {
		return handlers[hId];
	}

	// Setter
	inline void setHandler(hdlrId_type hId, Entity* e) {
		handlers[hId] = e;
	}
};