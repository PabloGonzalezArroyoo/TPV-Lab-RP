#include "FramedImage.h"#
#include "../sdlutils/SDLUtils.h"

// Constructora con los parametros necesarios 
FramedImage::FramedImage(Texture* _txt, int _fw, int _fh, int r, int c) :
				Image(_txt), fw(_fw), fh(_fh), rows(r), cols(c), frameNumber(r* c),
				startTime(SDLUtils::instance()->currRealTime()), currentFrame(0), src(SDL_Rect()) { }

void FramedImage::update() {
	// Si tengo que renderizar el siguiente frame
	if (sdlutils().currRealTime() - startTime >= FRAME_RATE) {
		// Actualizo mi contador
		startTime = sdlutils().currRealTime();

		// Actualizo el frame que debo renderizar
		currentFrame = currentFrame + 1 % frameNumber;

		// Crear el rectángulo fuente con el nuevo frame
		src.x = (currentFrame % cols) * fw;
		src.y = ((currentFrame / cols) % rows) * fh;
		src.w = fw;
		src.h = fh;
	}
}

// Renderizar con el rectangulo generado
void FramedImage::render() {
	texture->render(src, getRect());
}