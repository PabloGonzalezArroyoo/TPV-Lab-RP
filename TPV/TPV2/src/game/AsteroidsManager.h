#pragma once
#include <list>
#include "../components/Follow.h"

class AsteroidsManager
{
private:
	Manager* mn;
	list<Entity*> asts;
	int numAst;

public:
	AsteroidsManager(Manager* _mn);
	void createAsteroids(int n);
	void addAsteroidsFrequently();
	void destroyAllAsteroids();
	void OnCollision(Entity* a);
};