// Pr�ctica 3: Pablo Gonz�lez Arroyo, Rafael Argando�a Bl�cido
#pragma once
#include <list>
#include "Paddle.h"
#include "Ball.h"
#include "BlocksMap.h"
#include "Wall.h"
#include "Reward.h"
#include "Image.h"
#include "MenuButton.h"
#include "Game.h"

// Enum con el n� de la textura correspondiente dentro del array
enum TextureName { 
	BallTxt, Blocks, Digits, GameOver, PaddleTxt, SideWall, TopWall, Rewards,						// Objetos
	Winner, MainMenu, Pause,																		// Men�s
	PlayButton, LoadButton, ExitButton, ResumeButton, MainMenuButton, RestartButton, SaveButton		// Botones
};

class GameState
{
// Protected -> Accesible desde esta clase y sus herederas
protected:
	list<GameObject*> objects;
	Game* game;

public :
	// Constructoras y destructora
	GameState() { game = nullptr; };
	GameState(Game* g) { game = g; };
	virtual ~GameState();

	// M�todos esenciales
	virtual void update();
	virtual void render();
	virtual void handleEvent(SDL_Event e);

};

