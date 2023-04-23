#pragma once
#include "FighterSystem.h"

class GhostFighterSystem : public FighterSystem {
private:
	void applyRotation(int r);

public:
	static constexpr sysId id = _sys_GHOST_FIGHTER;

	void initSystem() override;
	void update() override;
};