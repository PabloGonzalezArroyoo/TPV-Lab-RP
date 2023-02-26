#pragma once
#include "Transform.h"

class DisableOnExit : public Component
{
private:
	Transform* myTr;
public:
	constexpr static cmpId_type id = _DISABLE_ON_EXIT;
	virtual void update();
	virtual void initComponent();
};

