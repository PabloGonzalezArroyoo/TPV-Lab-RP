#pragma once
#include "Transform.h"

class DisableOnExit : public Component
{
private:
	// Referencia a mi transform
	Transform* myTr;
public:
	// Id del componente
	constexpr static cmpId_type id = _DISABLE_ON_EXIT;

	//Métodos virtuales
	virtual void update();
	virtual void initComponent();
};

