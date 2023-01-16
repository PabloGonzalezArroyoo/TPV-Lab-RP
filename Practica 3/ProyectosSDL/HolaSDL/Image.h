// Práctica 3: Pablo González Arroyo, Rafael Argandoña Blácido
#pragma once
#include "GameObject.h"
#include <list>

// CLASE IMAGE - PROTOTIPO DE IMAGEN:
// Propiedades
//		- texture: puntero a la textura de la imagen
//		- pos: posición de la imagen
//		- w y h: tamaño de la imagen
// Metodos:
//		Constructora	-> Vacía y sobrecargada tanto con el puntero a la textura como con este y el resto de propiedades
//		Destructora		-> Llama al método del padre
//		render			-> renderiza la imagen

class Image : public GameObject
{
private:
	Texture* texture;
	Vector2D pos;
	uint w, h;
public:
	// Constructora y destructora
	Image() { texture = nullptr; }
	Image(Texture* _texture) { texture = _texture; pos = Vector2D(); w = WIN_WIDTH; h = WIN_HEIGHT; };
	Image(Texture* _texture, Vector2D _pos, uint _w, uint _h) { texture = _texture; pos = _pos; w = _w, h = _h; };
	virtual ~Image() {};

	// Métodos esenciales
	virtual void render() {
		SDL_Rect rect;
		rect.x = pos.getX(), rect.y = pos.getY();
		rect.w = w, rect.h = h;
		texture->render(rect);
	};
};

