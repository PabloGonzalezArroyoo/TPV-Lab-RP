#pragma once
#include <list>
#include "../components/Follow.h"
#include "../ecs/Manager.h"
#include "../components/FramedImage.h"
#include "../components/DisableOnEXit.h"

class Game;
class AsteroidsController
{
private:
	// Referencias al manager de la escena y a Game
	Manager* mng;
	Game* game;

	//Variables para el contador y contador de asteroides
	double startTime;
	double frameTime;
	int numAst;

public:
	// Constructora
	AsteroidsController(Manager* _mn, Game* g);

	// Creación de asteroides
	void createAsteroids(int n);
	void addAsteroidsFrequently();

	// Eliminación de asteroides
	void destroyAllAsteroids();
	void OnCollision(Entity* a);

	// Creación de parametros aleatorios de un asteroide nuevo
	Vector2D randomPos();
	Vector2D randomVel(Vector2D posAst);

	// Creacion de un asteroide hijo
	void createSon(Transform* father, int newGen);
};