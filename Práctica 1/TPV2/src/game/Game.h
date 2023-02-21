#pragma once
#include "../components/DeAcceleration.h"
#include "../components/DisableOnEXit.h"
#include "../components/FighterCtrl.h"
#include "../components/Follow.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../components/Gun.h"
#include "../components/Health.h"
#include "../components/Image.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Transform.h"

class Game : public Manager
{
private:
	Entity* player;
public:
	Game();
	~Game();

	virtual Entity* getPlayer() { return player; }
};