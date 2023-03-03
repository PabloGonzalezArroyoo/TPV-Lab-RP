#pragma once

#include "Image.h"

class FramedImage : public Image {
private:
	// Variables con informacion del spritesheet, el frame actual, el contador de tiempo y la ventana del frame ne la textura
	int fw, fh;
	int rows, cols;
	int currentFrame;
	float startTime;
	SDL_Rect src;

public:
	// Id del componente
	constexpr static cmpId_type id = _FRAMED_IMAGE;

	// Constructora
	FramedImage(Texture* _txt, int _fw, int _fh, int r, int c);

	// Métodos virtuales
	virtual void update();
	virtual void render();
};