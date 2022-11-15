#pragma once
#include "MovingObject.h"

enum RewardType {NextLevel, ExtraLife, ChangePaddle};

class Reward : public MovingObject {
private:
	RewardType rt;
};

