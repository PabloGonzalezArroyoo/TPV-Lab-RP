#pragma once
#include "Transform.h"

class Follow : public Component
{
private:
	Transform* myTr;
	Transform* plTr;
public:
	virtual void initComponent();
	virtual void update();
};