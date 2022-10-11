#include "Texture.h"
#include <iostream>

using namespace std;

// Elimina la textura
void Texture::free() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = 0;
}

// Carga la textura de X archivo 
void Texture::load(string filename, uint nRows, uint nCols) {
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());							// Se carga la imagen
	if (tempSurface == nullptr) throw "Error loading surface from " + filename;
	free();
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);					// Se crea una textura a partir de la imagen
	if (texture == nullptr) throw "Error loading texture from " + filename;
	numRows = nRows;
	numCols = nCols;
	w = tempSurface->w;																// Ancho y alto de la textura -> el de la imagen
	h = tempSurface->h;
	fw = w / numCols;																// Dimensión de cada frame (en base al nº frames de la propia imagen)
	fh = h / numRows;
	SDL_FreeSurface(tempSurface);													// Borras la imagen
}

void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;																// Cuadrado origen (de toda la imagen)
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);			// Poner al cuadrado destino la textura del origen
}

void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;																// Cuadrado origen (del frame)
	srcRect.x = fw * col;															// Seleccionar frame
	srcRect.y = fh * row;
	srcRect.w = fw;																	// Coges las dimensiones de ese frame
	srcRect.h = fh;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip);		// Poner al cuadrado destino la textura del origen
}