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
	Manager* mng;
	Game* game;
	int numAst;

	//Variables para el contador
	double startTime;
	double frameTime;
public:
	AsteroidsController(Manager* _mn, Game* g);
	void createAsteroids(int n);
	void addAsteroidsFrequently();
	void destroyAllAsteroids();
	void OnCollision(Entity* a);

	// Creación de asteroide
	Vector2D randomPos();
	Vector2D randomVel(Vector2D posAst);

	void createSon(Transform* father, int newGen);
};