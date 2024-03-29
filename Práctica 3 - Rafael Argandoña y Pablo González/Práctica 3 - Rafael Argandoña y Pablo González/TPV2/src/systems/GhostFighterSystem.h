#pragma once
#include "FighterSystem.h"

class GhostFighterSystem : public FighterSystem {
public:
	static constexpr sysId id = _sys_GHOST_FIGHTER;

	void initSystem() override;
	void receive(const Message& m) override;
	void update() override;
};