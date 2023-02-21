#pragma once
#include "Transform.h"

class DisableOnExit : public Component
{
private:
	Transform* myTr;
public:
	virtual void update();
	virtual void initComponent();
};

