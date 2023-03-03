#pragma once
#include "../sdlutils/SoundEffect.h"
#include "Transform.h"
class Game;
class FighterCtrl : public Component {
private:
	// Refencias a Game (para lanzar el estado de pausa), a mi transform y a mi sonido
	Game* game;
	Transform* tr;
	SoundEffect* sound;

	// Variables para el impulso al moverse, la rotation de la nave, limite de velocidad y controladores de tiempo
	float thrust;
	int r;
	float speedLimit;
	float startTime;
	float lastSoundTime;

public:
	constexpr static cmpId_type id = _FIGHTERCTRL;

	// Constructora
	FighterCtrl(Game* g, SoundEffect* _sound): Component(), game(g), tr(nullptr), 
		thrust(0.2), r(0), speedLimit(1.5), sound(_sound) {}
	
	// Métodos virtuales
	virtual void initComponent();
	virtual void update();

	// Input
	void handleInput();

	//Setter
	void setRot(int _rot) { r = _rot; }
};