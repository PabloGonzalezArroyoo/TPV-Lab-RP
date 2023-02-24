#pragma once
#include "Transform.h"

class DisableOnExit : public Component
{
private:
	Transform* myTr;
public:
	static const int id = _DISABLE_ON_EXIT;
	virtual void update();
	virtual void initComponent();
};

