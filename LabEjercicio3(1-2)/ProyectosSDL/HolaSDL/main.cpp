
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>

using namespace std;

using uint = unsigned int;

void firstTest() {
	// Inicialización
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	const uint winWidth = 800;
	const uint winHeight = 600;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Textura
	SDL_Texture* txtBg;												// Textura del background
	string filename = "../images/background1.png";					// Nombre del fichero con la imagen
	SDL_Surface* surface = IMG_Load(filename.c_str());
	txtBg = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);										// Se borra la estructura auxiliar

	// Textura perro
	SDL_Texture* txtDog;											// Textura del perro
	filename = "../images/dog.png";									// Nombre del fichero con la imagen
	surface = IMG_Load(filename.c_str());
	txtDog = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);										// Se borra la estructura auxiliar

	// Textura helicoptero
	SDL_Texture* txtHel;											// Textura del helicoptero
	filename = "../images/helicopter.png";							// Nombre del fichero con la imagen
	surface = IMG_Load(filename.c_str());
	txtHel = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);										// Se borra la estructura auxiliar

	// Posición del perro por pantalla
	int textW, textH;												// Para saber el tamaño de la textura
	SDL_QueryTexture(txtDog, nullptr, nullptr, &textW, &textH);
	SDL_Rect srcDog, destDog;
	srcDog.w = textW / 6, srcDog.h = textH;							// Tamaño frame textura
	uint cellW = winWidth / 6, cellH = winHeight / 6;				// Dividir pantalla en matriz de X celdas
	destDog.w = cellW, destDog.h = cellH;							// Tamaño de de la celda de salida
	srcDog.x = srcDog.y = 0;										// Celda (0, 0) del origen
	destDog.x = 0 * cellW, destDog.y = 4 * cellH;					// Celda (0, 4) proporcional de destino

	// Posición del helicoptero por pantalla
	SDL_QueryTexture(txtHel, nullptr, nullptr, &textW, &textH);		// Para saber el tamaño de la textura
	SDL_Rect srcHel, destHel;
	srcHel.w = textW / 5, srcHel.h = textH;							// Tamaño frame textura
	destHel.w = cellW, destHel.h = cellH;							// Tamaño de de la celda de salida
	srcHel.x = srcHel.y = 0;										// Celda (0, 0) del origen
	destHel.x = 5 * cellW, destHel.y = 0 * cellH;					// Celda (5, 0) proporcional de destino

	// Constantes de tiempo de animaciones
	const int timeLimit = 5000;

	// Variables velocidad
	int dogMov = 50, dogAnim = 100;
	int helMov = 50, helAnim = 200;

	// Renderizado
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else {
		uint32_t startTime = SDL_GetTicks(), frameTime;					// Variables de control de flujo y tiempo
		bool exit = false, dogStop = false, helStop = false;			// Control de salida

		/* // Bucle sin usar eventos
		while (!exit) {													// Mientras hay eventos pendientes y no se ha salido
			if (false) exit = true;										// Si quit, entonces salir
			else {
				frameTime = SDL_GetTicks() - startTime;					// Tiempo desde la última actualización (delta time)
				
				if (frameTime >= timeLimit) exit = true;				// Salir del bucle si se superan los 5 segundos
				else if (frameTime % 50 == 0) {							// Hacer un movimiento cada vez que el tiempo entre frames es divisor de 3
					if (destDog.x >= winWidth) destDog.x = 0;			// Volver a la posición incial
					else destDog.x += 15;								// Mover aproximadamente 10 píxeles cada vez

					if (destHel.x <= 0) destHel.x = winWidth;			// Volver a la posición incial
					else destHel.x -= 15;								// Mover aproximadamente 10 píxeles cada vez
				}
			}
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, txtBg, nullptr, nullptr);			// Render textura background

			srcDog.x = srcDog.w * int((SDL_GetTicks() / refreshDog) % 6);	// Seleccionar frame de la imagen origen cada X milisegundos
			SDL_RenderCopy(renderer, txtDog, &srcDog, &destDog);		// Render perro

			srcHel.x = srcHel.w * int((SDL_GetTicks() / refreshHel) % 5);	// Seleccionar frame de la imagen origen cada X milisegundos
			SDL_RenderCopy(renderer, txtHel, &srcHel, &destHel);		// Render helicoptero

			SDL_RenderPresent(renderer);								// Muestra la escena
		} */
		// SDL_Delay(2000);												// Esperar 2 segundos

		// Bucle manegando eventos
		SDL_Event event, eventDog, eventHel;
		while (!exit) {
			while (SDL_PollEvent(&event) && !exit) {					// Mientras quedan eventos pendientes y no se ha salido
				if (event.type == SDL_QUIT) exit = true;				// Salir si cerramos ventana
				else if (event.type == SDL_KEYDOWN) {					// Si se pulsa una tecla
					if (event.key.keysym.sym == SDLK_d) dogStop = !dogStop;	// Parar/reanudar el perro si se pulsa la tecla d
					else if (event.key.keysym.sym == SDLK_h) helStop = !helStop; // Parar/reanudar el helicóptero si se pulsa la tecla h
					else if (event.key.keysym.sym == SDLK_f) { dogMov /= 2; dogAnim /= 2; }
					else if (event.key.keysym.sym == SDLK_s) { dogMov *= 2; dogAnim *= 2; }
					else if (event.key.keysym.sym == SDLK_j) { helMov /= 2; helAnim /= 2; }
					else if (event.key.keysym.sym == SDLK_g) { helMov *= 2; helAnim *= 2; }
				}
			}

			frameTime = SDL_GetTicks() - startTime;						// Tiempo desde la última actualización (delta time)
			if (!dogStop) {
				if (frameTime % dogMov == 0) {							// Hacer un movimiento cada vez que el tiempo entre frames es divisor de 3
					if (destDog.x >= winWidth) destDog.x = 0;			// Volver a la posición incial
					else destDog.x += 15;								// Mover aproximadamente 10 píxeles cada vez
				}
				srcDog.x = srcDog.w * int((SDL_GetTicks() / dogAnim) % 6);	// Seleccionar frame de la imagen origen cada X milisegundos
			}

			if (!helStop) {
				if (frameTime % helMov == 0) {							// Hacer un movimiento cada vez que el tiempo entre frames es divisor de 3
					if (destHel.x <= 0) destHel.x = winWidth;			// Volver a la posición incial
					else destHel.x -= 15;								// Mover aproximadamente 10 píxeles cada vez
				}
				srcHel.x = srcHel.w * int((SDL_GetTicks() / helAnim) % 5);	// Seleccionar frame de la imagen origen cada X milisegundos
			}

			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, txtBg, nullptr, nullptr);			// Render textura background
			SDL_RenderCopy(renderer, txtDog, &srcDog, &destDog);		// Render perro
			SDL_RenderCopy(renderer, txtHel, &srcHel, &destHel);		// Render helicoptero

			SDL_RenderPresent(renderer);								// Muestra la escena
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[]){
	firstTest();
	return 0;
}