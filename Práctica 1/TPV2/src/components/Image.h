#pragma once

#include "Transform.h"
#include "../sdlUtils/Texture.h"

class Image : public Component {
protected:
	Texture* texture;
	Transform* tr;

public:
	// Constructoras
	Image() : Component() { }
	Image(Texture* _txt) : Component(), texture(_txt) { }

	// M�todos virtuales
	virtual void initComponent();
	virtual void render();

	// Getter
	virtual SDL_Rect getRect() const;
};