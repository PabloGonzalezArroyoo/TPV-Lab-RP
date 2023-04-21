#pragma once
#include "../ecs/Manager.h"

struct FighterCtrl : public Component {
private:
	float thrust;
	int r;
	float speedLimit;

public:
	constexpr static cmpId_type id = _FIGHTERCTRL;

	// Constructora
	inline FighterCtrl(float rot) : Component(), thrust(0.2), r(rot), speedLimit(1.5) { }

	// Getters y setters
	int getRot() { return r; }
	void setRot(int _r) { r = _r; }
	float getThrust() { return thrust; }
	float getSpeedLimit() { return speedLimit; }
};