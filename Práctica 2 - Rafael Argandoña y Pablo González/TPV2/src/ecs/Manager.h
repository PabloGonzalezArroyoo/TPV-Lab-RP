#pragma once
#include "Entity.h"
#include "Component.h"
#include "System.h"
#include <vector>
#include <array>

using namespace std;

class Manager {
private:
	// Estructura de entidades -> array de vectores
	array<vector<Entity*>, maxGroupId> entsByGroup;
	array<Entity*, maxHandlerId> handlers;
	array<System*, maxSystemId> sys;
	vector<Message> msgs;
	vector<Message> aux_msgs;
	 
public: 
	// Constructora y destructora
	Manager();
	virtual ~Manager();

	// Métodos esenciales
	void refresh();
	void update();
	void render();

	// ----- METODOS QUE AÑADEN -----
	// Añade un componente y devuelve un puntero a este
	template<typename T, typename ...Ts>
	inline T* addComponent(Entity* e, Ts&&...args) {
		T* c = new T(std::forward<Ts>(args)...);
		constexpr cmpId_type cId = T::id;
		removeComponent<T>(e);
		e->currCmps.push_back(c);
		e->cmps[cId] = c;
		c->setContext(e, this);
		c->initComponent();
		return c;
	}

	// Para añadir una entidad al manager
	Entity* addEntity(grpId_type gId = _grp_GENERAL);

	// Para añadir un sistema
	template<typename T, typename ...Ts>
	inline T* addSystem(Ts &&... args) {
		constexpr sysId_type sId = T::id;
		removeSystem<T>();
		System* s = new T(std::forward<Ts>(args)...);
		s->setContext(this);
		s->initSystem();
		sys[sId] = s;
		return static_cast<T*>(s);
	}

	// ----- METODOS QUE QUITAN -----
	// Borra el componente de la entidad
	template<typename T>
	inline void removeComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		if (e->cmps[cId] != nullptr) {
			auto iter = std::find(e->currCmps.begin(),
				e->currCmps.end(),
				e->cmps[cId]);
			e->currCmps.erase(iter);
			delete e->cmps[cId];
			e->cmps[cId] = nullptr;
		}
	}
	// Elimina todas las entidades de un grupo deseado
	void removeEntities(grpId_type gId) {
		for (Entity* e : entsByGroup[gId]) {
			e->alive = false;
		}
	}

	// Elimina un sistema
	template<typename T>
	inline void removeSystem() {
		constexpr sysId_type sId = T::id;
		if (sys[sId] != nullptr) {
			delete sys[sId];
			sys[sId] = nullptr;
		}
	}

	//	----- GETTERS -----
	// Devuelve un puntero al componente
	template<typename T>
	inline T* getComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		return static_cast<T*>(e->cmps[cId]);
	}

	// Devuelve un grupo de entidades
	inline const auto& getEntities(grpId_type gId = _grp_GENERAL) {
		return entsByGroup[gId];
	}

	// Devuelve un objeto especifico
	inline Entity* getHandler(hdlrId_type hId) {
		assert(handlers[hId] != nullptr);
		return handlers[hId];
	}

	// Devuelve el sistema especifico
	template<typename T>
	inline T* getSystem() {
		constexpr sysId_type sId = T::id;
		return static_cast<T*>(sys[sId]);
	}

	// ----- SETTERS -----
	inline void setHandler(hdlrId_type hId, Entity* e) {
		handlers[hId] = e;
	}

	inline void setAlive(Entity* e, bool alive) {
		e->alive = alive;
	}

	// ----- CHECKERS -----
	// Comprueba si tiene el componente
	template <typename T>
	inline bool hasComponent(Entity* e) {
		constexpr cmpId_type cId = T::id;
		return e->cmps[cId] != nullptr;
	}

	// Comprueba si la entidad está viva
	inline bool isAlive(Entity* e) {
		return e->alive;
	}

	// ----- MESSAGES -----
	inline void send(const Message& m, bool delay = false) {
		if (!delay) {
			for (System* s : sys) {
				if (s != nullptr)
					s->receive(m);
			}
		}
		else {
			msgs.emplace_back(m);
		}
	}

	inline void flushMessages() {
		std::swap(msgs, aux_msgs);
		for (auto& m : aux_msgs) {
			for (System* s : sys) {
				if (s != nullptr)
					s->receive(m);
			}
		}
		aux_msgs.clear();
	}
};