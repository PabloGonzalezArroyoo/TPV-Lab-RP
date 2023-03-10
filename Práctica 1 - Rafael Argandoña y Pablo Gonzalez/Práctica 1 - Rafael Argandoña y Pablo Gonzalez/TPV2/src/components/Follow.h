#pragma once
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class Follow : public Component
{
private:
	// Referencias a mi transform y al transform del jugador
	Transform* myTr;
	Transform* plTr;
	// Variable para tener una velocidad aleatoria
	float randomSpeed;
public:
	// Id del componente
	constexpr static cmpId_type id = _FOLLOW;

	//Constructor
	Follow() : Component(), myTr(nullptr), plTr(nullptr)  { 
		float ran = SDLUtils::instance()->rand().nextInt(1, 6);
		randomSpeed =  ran / 10.0f;
	}

	//Métodos virtuales
	virtual void initComponent();
	virtual void update();
};