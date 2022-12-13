#include "MenuButton.h"

MenuButton::MenuButton() {
	pos = Vector2D();
	texture = nullptr;
}

MenuButton::MenuButton(Vector2D _pos, Texture* _txt, void (*callback)(Game* g)) {
	pos = _pos;
	texture = _txt;
	myC = callback;
}

void MenuButton::render() {
	SDL_Rect myRect;
	myRect.x = pos.getX(); myRect.y = pos.getY();
	myRect.w = WIDTH; myRect.h = HEIGHT;
	texture->renderFrame(myRect, 0, state);
}

void MenuButton::handleEvent(SDL_Event e) {
	while (SDL_PollEvent(&e)) {
		// Si se hace clic
		if (e.type == SDL_MOUSEBUTTONDOWN && state == OnOver) { myC; state = OnClick; }//Llamar a x funcion
		else if (e.type == SDL_MOUSEMOTION);
	}
}

void MenuButton::update() {
	int mPosX = 0, mPosY = 0;
	SDL_GetGlobalMouseState(&mPosX, &mPosY);

	if ((mPosX >= pos.getX() && mPosX < pos.getX() + WIDTH) && (mPosY >= pos.getY() && mPosY < pos.getY() + HEIGHT)) {		// Si pulsa dentro del rect�ngulo de play
		state = OnOver;
	}

	else state = OnOut;
}