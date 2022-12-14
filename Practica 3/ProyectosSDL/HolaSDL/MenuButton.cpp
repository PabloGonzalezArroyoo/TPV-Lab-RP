#include "MenuButton.h"

MenuButton::MenuButton() {
	pos = Vector2D();
	texture = nullptr;
	state = OnOut;
}

MenuButton::MenuButton(Vector2D _pos, Texture* _txt, Callback* _c) {
	pos = _pos;
	texture = _txt;
	myC = _c;
	state = OnOut;
}

void MenuButton::render() {
	SDL_Rect myRect;
	myRect.x = pos.getX(); myRect.y = pos.getY();
	myRect.w = BUTTON_WIDTH; myRect.h = BUTTON_HEIGHT;
	texture->renderFrame(myRect, 0, state);
}

void MenuButton::handleEvent(SDL_Event e) {
	if (e.type == SDL_MOUSEBUTTONDOWN && state == OnOver) { state = OnClick; }
}

void MenuButton::update() {
	int mPosX = 0, mPosY = 0;
	SDL_GetMouseState(&mPosX, &mPosY);
	if ((mPosX >= pos.getX() && mPosX < pos.getX() + BUTTON_WIDTH) && (mPosY >= pos.getY() && mPosY < pos.getY() + BUTTON_HEIGHT)) {		// Si pulsa dentro del rect�ngulo de play
		state = OnOver;
	}
	else state = OnOut;
}