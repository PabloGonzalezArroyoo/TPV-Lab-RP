#include "Menu.h"

Menu::Menu(Texture* _texture) {
	texture = _texture;
}

void Menu::render() {
	SDL_Rect rect;
	rect.x = 0, rect.y = 0;
	rect.w = WIN_WIDTH, rect.h = WIN_HEIGHT;
	texture->render(rect);
}