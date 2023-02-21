#include "FramedImage.h"

FramedImage::FramedImage(Texture* _txt, int _fw, int _fh, int r, int c) : 
				Image(_txt), fw(_fw), fh(_fh), rows(r), cols(c), startTime(SDL_GetTicks()), currentFrame(0), src(SDL_Rect()) { }

void FramedImage::update() {
	if (SDL_GetTicks() - startTime >= 50) {
		startTime = SDL_GetTicks();
		currentFrame = currentFrame + 1 % 3;

		src.x = (currentFrame % cols) * fw;
		src.y = ((currentFrame / cols) % rows) * fh;
		src.w = fw;
		src.h = fh;
	}
}

void FramedImage::render() {
	texture->render(src, getRect());
}