#pragma once
#include "Transform.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Manager.h"

// ESTA CLASE NO DEBERÍA EXISTIR

struct Image : public Component {
private:
	Transform* tr;
	Texture* txt;
public:
	constexpr static cmpId_type id = _IMAGE;

	Image(Texture* _t) : Component() , txt(_t) { }

	inline virtual void initComponent() { tr = mngr->getComponent<Transform>(ent);	}

	// GETTERS
	inline Texture* getImageTexture() { return txt; }
	inline SDL_Rect getRect() const {
		SDL_Rect r;
		r.x = tr->getPosition().getX();
		r.y = tr->getPosition().getY();
		r.w = tr->getWidth();
		r.h = tr->getHeight();
	}
};