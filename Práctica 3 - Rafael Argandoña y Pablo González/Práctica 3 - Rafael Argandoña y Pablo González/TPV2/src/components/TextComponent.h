#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"

class TextComponent : public Component {
private:
	Texture* txt;
public:
	static constexpr cmpId_type id = _TEXT;

	TextComponent(Texture* _t) : Component(), txt(_t) { }

	Texture* getTexture() { return txt; }
};