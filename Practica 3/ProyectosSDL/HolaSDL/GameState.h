#pragma once
#include <list>
#include "GameObject.h"
#include "MenuButton.h"

// Enum con el n� de la textura correspondiente dentro del array
enum TextureName { BallTxt, Blocks, Digits, GameOver, PaddleTxt, SideWall, TopWall, Winner, Rewards, MainMenu, 
					PlayButton, LoadButton, ExitButton, ResumeButton, MainMenuButton, RestartButton };

class Game;
class GameState
{
// Protected -> Accesible desde esta clase y sus herederas
protected:
	list<GameObject*> objects;
	Game* game = nullptr;

public :
	GameState() { game = nullptr; };
	GameState(Game* g) { game = g; };
	virtual ~GameState();

	virtual void update();
	virtual void render();
	virtual void handleEvent(SDL_Event e);
};

