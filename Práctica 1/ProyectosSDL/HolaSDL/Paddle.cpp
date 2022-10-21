#include "Paddle.h"

// Constructora
Paddle::Paddle(Vector2D v, int width, int height, Vector2D velocity, Texture* txt) {
	pos = v; w = width; h = height; vel = velocity; texture = txt;
}

Paddle::~Paddle() {
	pos = vel = Vector2D();
	w = h = 0;
	delete(texture);
}

void Paddle::render() {
	SDL_Rect dest;
	dest.x = (int)pos.getX(); dest.y = (int)pos.getY();
	dest.w = w; dest.h = h;
	texture->render(dest);
}

void Paddle::update(int dir) {
	vel = Vector2D(dir, 0);																// Crear vector dirección
	pos = pos + vel;																	// Aplicarlo
}

void Paddle::handleEvents(SDL_Event e) {
	if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT) update(1);		// Si pulsamos "d" o "->", x++
	else if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT) update(-1);	// Si pulsados "a" o "<-", x--;
	else update(0);																		// Si no se pulsa nada, se queda quieto
}

void Paddle::collision() {

}