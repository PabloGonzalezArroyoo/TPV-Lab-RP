#include "RenderSystem.h"
#include "../ecs/Manager.h"

void RenderSystem::receive(const Message& m) {
	if (m.id == _m_INIT_STATE) {
		state = m._state_data.st;
	}
}

void RenderSystem::initSystem() {
	startTime = sdlutils().currRealTime();
}

void RenderSystem::update() {
	//SDL_RenderClear(sdlutils().renderer());
	
	renderGroup(_grp_GENERAL, FIGHTER);
	renderGroup(_grp_BULLETS, FIRETXT);
	renderAsteroids();
	if (state == PLAY_STATE || state == PAUSE_STATE) renderUI();
	// renderText();

	//SDL_RenderPresent(sdlutils().renderer());
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

void RenderSystem::renderAsteroids() {		
	auto asts = mngr->getEntities(_grp_ASTEROIDS);
	Transform* tr = nullptr;
	FramedImage* fi = nullptr;
	int frame = 0;

	for (int i = 0; i < asts.size(); i++) {
		fi = mngr->getComponent<FramedImage>(asts[i]);
		tr = mngr->getComponent<Transform>(asts[i]);
		frame = fi->getCurrentFrame();

		fi->getImageTexture()->render(fi->getSrcRect(), tr->getRect()); 
		
		if (sdlutils().currRealTime() - startTime >= FRAME_RATE) fi->setCurrentFrame(frame + 1);
	}

	if (sdlutils().currRealTime() - startTime >= FRAME_RATE) startTime = sdlutils().currRealTime();
}

void RenderSystem::renderTexts() const {
	// TODO
}

void RenderSystem::renderUI() const{
	Health* h = mngr->getComponent<Health>(mngr->getHandler(_hdlr_FIGHTER));
	Texture* text = &sdlutils().images().at(HEART);
	SDL_Rect rect;
	rect.x = UPPER_LEFT_CORNER_X;
	rect.y = UPPER_LEFT_CORNER_Y;
	rect.w = text->width() / 4;
	rect.h = text->height() / 4;

	for (int i = 0; i < h->getLifes(); i++) {
		rect.x = UPPER_LEFT_CORNER_X + i * (rect.w + 5);
		text->render(rect);
	}
}

void RenderSystem::renderGroup(grpId_type group, string key) const {
	vector<Entity*> entities = mngr->getEntities(group);
	Transform* tr = nullptr;
	for (int i = 0; i < entities.size(); i++) {
		tr = mngr->getComponent<Transform>(entities[i]);
		Texture* txt = &sdlutils().images().at(key);
		txt->render(tr->getRect(), tr->getRotation());
	}
}