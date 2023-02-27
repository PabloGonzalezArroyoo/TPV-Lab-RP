#pragma once
#include <list>
#include "../components/Follow.h"
#include "../ecs/Manager.h"
#include "../components/FramedImage.h"

class AsteroidsController
{
private:
	Manager* mng;
	int numAst;

public:
	AsteroidsController(Manager* _mn);
	void createAsteroids(int n);
	void addAsteroidsFrequently();
	void destroyAllAsteroids();
	void OnCollision(Entity* a);

	// Creación de asteroide
	Vector2D randomPos();
	Vector2D randomVel();
};