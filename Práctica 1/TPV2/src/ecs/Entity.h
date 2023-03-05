#pragma once
#include <vector>
#include <array>
#include "Component.h"
#include "../utils/Constants.h"
using namespace std;

class Manager;
class Entity {
protected:
	Manager* myMng = nullptr;
	std::vector<Component*> currCmps;
	std::array<Component*, maxComponentId> cmps;
	bool alive;

public:
	// Constructora
	Entity(): alive(true), myMng(nullptr), cmps(), currCmps() {
		currCmps.reserve(maxComponentId);
	}

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

	// Asignar puntero al manager
	inline void setContext(Manager* mng) { myMng = mng; }

	// Inicializar entidad
	virtual void initEntity() {};

	// Comprobar y asignar alive
	inline bool isAlive() { return alive; }
	inline void setAlive(bool a) { alive = a; }

	// Añade un componente y devuelve un puntero a este
	template<typename T, typename ...Ts>
	inline T* addComponent(Ts&&...args) {
		T* c = new T(std::forward<Ts>(args)...);
		constexpr cmpId_type cId = T::id;
		removeComponent<T>();
		currCmps.push_back(c);
		cmps[cId] = c;
		c->setContext(this, myMng);
		c->initComponent();
		return c;
	}

	// Borra el componente de la entidad
	template<typename T>
	inline void removeComponent() {
		constexpr cmpId_type cId = T::id;
		if (cmps[cId] != nullptr) {
			auto iter = std::find(currCmps.begin(),
				currCmps.end(), cmps[cId]);
				currCmps.erase(iter);
				delete cmps[cId];
				cmps[cId] = nullptr;
		}
	}

	// Devuelve un puntero al componente
	template<typename T>
	inline T* getComponent() {
		constexpr cmpId_type cId = T::id;
		return static_cast<T*>(cmps[cId]);
	}

	// Comrpueba si tiene el componente
	template <typename T>
	inline bool hasComponent() {
		constexpr cmpId_type cId = T::id;
		return cmps[cId] != nullptr;
	}

	// Métodos virtuales
	virtual void update() {
		for (Component* cmp : currCmps) cmp->update();
	}
	virtual void render() const{
		for (Component* cmp : currCmps) cmp->render();
	}
	virtual void handleInput() {
		for (Component* cmp : currCmps) cmp->handleInput();
	}
};