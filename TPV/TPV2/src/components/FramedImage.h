#pragma once

#include "Image.h"

class FramedImage : public Image {
private:
	int currentFrame;
	float startTime;
	int fw, fh;
	int rows, cols;
	SDL_Rect src;

public:
	constexpr static cmpId_type id = _FRAMED_IMAGE;

	FramedImage(Texture* _txt, int _fw, int _fh, int r, int c);

	virtual void update();
	virtual void render();
};