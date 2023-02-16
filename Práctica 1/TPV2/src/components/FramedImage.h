#pragma once

#include "Image.h"

class FramedImage : public Image {
private:
	int frame;
public:
	FramedImage();

	virtual void render();
};