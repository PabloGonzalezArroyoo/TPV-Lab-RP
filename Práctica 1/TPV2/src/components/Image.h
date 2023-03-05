#pragma once

#include "Transform.h"
#include "../sdlUtils/Texture.h"

class Entity;
class Image : public Component {
protected:
	// Referencia a la textura que debemos renderizar y a mi transform
	Texture* texture;
	Transform* tr;

public:
	// Id del componente
	constexpr static cmpId_type id = _IMAGE;

	// Constructoras
	Image() : Component(), texture(nullptr), tr(nullptr) { }
	Image(Texture* _txt) : Component(), texture(_txt), tr(nullptr) { }

	// Métodos virtuales
	virtual void initComponent();
	virtual void render();

	// Getter
	virtual SDL_Rect getRect() const;
};