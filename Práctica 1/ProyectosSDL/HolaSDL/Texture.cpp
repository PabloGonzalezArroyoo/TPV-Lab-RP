#include "Texture.h"
#include <iostream>

using namespace std;

void Texture::wipe() {
	SDL_DestroyTexture(texture);
	texture = nullptr;
	w = h = 0;
}

void Texture::load(string filename, uint nRows, uint nCols) {
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());					// Cargar la imagen en una variable auxiliar
	if (tempSurface == nullptr) throw "Error: image not found (" + filename + ") ";	// Si no la encuentra, lanza una excepción
	wipe();																	// Destruir textura previa
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);			// Creamos la textura a partir de la superficie que contiene la imagen
	if (texture == nullptr) throw "Error: texture not loaded (" + filename + ") "; // Si no se carga la textura correctamente, excepción
	numRows = nRows;														// Asignar columnas y filas
	numCols = nCols;
	w = tempSurface->w;														// Asignar width y height
	h = tempSurface->h;
	fw = w / numCols;														// Dimensiones del frame
	fh = h / numRows;

	SDL_FreeSurface(tempSurface);											// Borra el objeto auxiliar de la imagen
}

void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;														// Crear rectangulo de toda la imagen origen
	srcRect.x = 0, srcRect.y = 0;
	srcRect.w = w, srcRect.h = h;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0, 0, flip);	// Renderizar una textura entera
}

void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = fw * col;													// Colocarnos en el frame deseado de la imagen
	srcRect.y = fh * row;
	srcRect.w = fw;															// Coincidir tamaño de la ventana con el del frame
	srcRect.h = fh;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, 0, flip); // Renderizar una textura entera
}