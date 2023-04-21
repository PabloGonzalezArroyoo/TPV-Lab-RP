#pragma once

struct FramedImage : public Component {
private:
	int fw, fh;
	int rows, cols;
	int frameNumber;
	int currentFrame;
	SDL_Rect src;
	Texture* txt;

public:
	constexpr static cmpId_type id = _FRAMED_IMAGE;
	
	FramedImage(Texture* txt, int _fw, int _fh, int r, int c) : Component(), txt(txt), fw(_fw), fh(_fh), rows(r), cols(c),
																frameNumber(r*c), currentFrame(0), src(SDL_Rect()) {	}

	// GETTERS
	inline int getCurrentFrame() { return currentFrame; }
	inline int getTotalFrames() { return frameNumber; }
	inline SDL_Rect getSrcRect() {
		src.x = (currentFrame % cols) * fw;
		src.y = ((currentFrame / cols) % rows) * fh;
		src.w = fw; src.h = fh;
		return src;
	}
	inline Texture* getImageTexture() { return txt; }

	// SETTERS
	inline void setCurrentFrame(int _cf) { currentFrame = _cf; }
};