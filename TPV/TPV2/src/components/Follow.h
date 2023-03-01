#pragma once
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class Follow : public Component
{
private:
	Transform* myTr;
	Transform* plTr;
	float randomSpeed;
public:
	constexpr static cmpId_type id = _FOLLOW;
	Follow() : Component(), myTr(nullptr), plTr(nullptr)  { 
		float ran = SDLUtils::instance()->rand().nextInt(1, 6);
		randomSpeed =  ran / 10.0f;
	}
	virtual void initComponent();
	virtual void update();
};