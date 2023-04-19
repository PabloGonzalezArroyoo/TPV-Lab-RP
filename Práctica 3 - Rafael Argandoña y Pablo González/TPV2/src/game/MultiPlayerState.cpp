#include "MultiPlayerState.h"

MultiPlayerState::MultiPlayerState() {
	mng = new Manager();

	mng->addSystem<NetworkSystem>();
}