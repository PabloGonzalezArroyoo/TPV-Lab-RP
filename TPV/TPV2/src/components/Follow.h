#pragma once
#include "Transform.h"

class Follow : public Component
{
private:
	Transform* myTr;
	Transform* plTr;
public:
	constexpr static cmpId_type id = _FOLLOW;

	virtual void initComponent();
	virtual void update();
};