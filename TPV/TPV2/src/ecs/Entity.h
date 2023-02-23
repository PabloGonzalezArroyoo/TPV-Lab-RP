#pragma once
#include <vector>
#include <array>
#include "Component.h"
#include "../game/ecs_def.h"

class Manager;
class Entity {
protected:
	bool alive;
	Manager* myMng;
	std::vector<Component*> currCmps;
	std::array<Component*, maxComponentId> cmps;

public:
	Entity(): alive(true), myMng(nullptr), cmps(), currCmps() {
		currCmps.reserve(maxComponentId);
	}

	~Entity() {
		for (Component* cmp : currCmps) {
			delete cmp;
			cmp = nullptr;
		}
		for (Component* cmp : cmps) {
			cmp = nullptr;
		}
	}

	inline void setContext(Manager* mng) { myMng = mng; }

	virtual void initEntity();

	inline bool isAlive() { return alive; }
	inline void setAlive(bool a) { alive = a; }

	template<typename T, typename ...Ts>
	inline T* addComponent(Ts&&...args) {
		T* c = new T(std::forward<Ts>(args)...);
		removeComponent<T>();

		currCmps.push_back(c);
		c->setContext(this, myMng);
		c->initComponent();
		return c;
	}

	template<typename T>
	inline void removeComponent() {
		constexpr cmpId_type cId = T::id;

		if (cmps[cId] != nullptr) {
			auto iter = std::find(currCmps.begin()),
				currCmps.end(), cmps[cid]);
				currCmps.erase(iter);
				delete cmps[cId];
				cmps[cId] = nullptr;
		}
	}

	template<typename T>
	inline T* getComponent() {
		return static_cast<T*>(cmps[T::id]);
	}

	template <typename T>
	inline bool hasComponent() {
		return cmps[T::id] != nullptr;
	}

	virtual void update() {
		for (Component* cmp : currCmps) {
			cmp->update();
		}
	}

	virtual void render() const{
		for (Component* cmp : currCmps) {
			cmp->render();
		}
	}

	virtual void handleInput() {
		for (Component* cmp : currCmps) {
			cmp->handleInput();
		}
	}
};