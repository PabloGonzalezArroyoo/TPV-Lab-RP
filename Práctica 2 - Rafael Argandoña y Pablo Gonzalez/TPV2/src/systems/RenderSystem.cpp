#include "RenderSystem.h"

void RenderSystem::receive(const Message& m) {

}

void RenderSystem::initSystem() {

}

void RenderSystem::update() {
	SDL_RenderClear(sdlutils().renderer());
	
	SDL_RenderPresent(sdlutils().renderer());
}

void RenderSystem::onRoundStart() {

}

void RenderSystem::onRoundOver() {

}

void RenderSystem::onGameOver() {
	
}

void RenderSystem::onGameStart() {
	SDL_SetRenderDrawColor(sdlutils().renderer(), 0, 123, 17, 1);
}

SDL_Rect RenderSystem::getRect(Transform* tr) {
	SDL_Rect r;
	r.x = tr->getPosition().getX();
	r.y = tr->getPosition().getY();
	r.w = tr->getWidth();
	r.h = tr->getHeight();

	return r;
}