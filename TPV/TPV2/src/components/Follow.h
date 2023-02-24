#pragma once
#include "Transform.h"

class Follow : public Component
{
private:
	Transform* myTr;
	Transform* plTr;
public:
	static const int id = _FOLLOW;

	virtual void initComponent();
	virtual void update();
};