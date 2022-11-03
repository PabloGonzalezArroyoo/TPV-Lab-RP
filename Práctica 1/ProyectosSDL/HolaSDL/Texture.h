#pragma once

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows

#include <string>

using namespace std;

typedef unsigned int uint;

class Texture {
private:
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;
	uint w = 0, h = 0, fw = 0, fh = 0;
	uint numCols = 1, numRows = 1;

public:
	Texture(SDL_Renderer* r) : renderer(r){};
	Texture(SDL_Renderer* r, string filename, uint nRows = 1, uint nCols = 1) : renderer(r) { load(filename, nRows, nCols); };
	~Texture() { wipe(); };
	void wipe();

	int getW() const { return w; };
	int getH() const { return h; };
	uint getNumCols() const { return numCols; };
	uint getNumRows() const { return numRows; };
	SDL_Texture* getTexture() const { return texture; };

	void load(string filename, uint nRows = 1, uint nCols = 1);
	void render(const SDL_Rect& destRect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};

