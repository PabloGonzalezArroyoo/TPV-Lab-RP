#pragma once
#include <vector>
#include <array>
#include "Component.h"
#include "../utils/Constants.h"
using namespace std;

class Manager;
class Entity {
private:
	friend Manager;
protected:
	vector<Component*> currCmps;
	array<Component*, maxComponentId> cmps;
	bool alive;
	grpId_type gId_;

public:
	// Constructora
	Entity(grpId_type gId): alive(true), gId_(gId), cmps(), currCmps() {
		currCmps.reserve(maxComponentId);
	}
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	// Destructora
	~Entity() {
		for (Component* cmp : currCmps) {
			delete cmp;
			cmp = nullptr;
		}
		for (Component* cmp : cmps) {
			cmp = nullptr;
		}
	}

	// Inicializar entidad
	virtual void initEntity() {};
};