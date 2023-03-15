#include "AsteroidsSystem.h"


void AsteroidsSystem::onCollision_AsteroidBullet(Entity* a) {
	
}

Vector2D AsteroidsSystem::randomPos() {
	int x = 0, y = 0;

	// Lado de la pantalla
	switch (sdlutils().rand().nextInt(0, 4)) {
		// Arriba
	case 0:
		y = sdlutils().rand().nextInt(0, 10);
		x = sdlutils().rand().nextInt(0, WIN_WIDTH);
		break;
		// Izquierda
	case 1:
		y = sdlutils().rand().nextInt(0, WIN_HEIGHT);
		x = sdlutils().rand().nextInt(0, 10);
		break;
		// Derecha
	case 2:
		y = sdlutils().rand().nextInt(0, WIN_HEIGHT);
		x = sdlutils().rand().nextInt(WIN_WIDTH - 10, WIN_WIDTH);
		break;
		// Abajo
	case 3:
		y = sdlutils().rand().nextInt(WIN_HEIGHT - 10, WIN_HEIGHT);
		x = sdlutils().rand().nextInt(0, WIN_WIDTH);
		break;
	}

	return Vector2D(x, y);
}

// Calcular una velocidad aleatoria
Vector2D AsteroidsSystem::randomVel(Vector2D posAst) {
	// Calcular un aleatorio
	float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;

	// Calcular el vector
	Vector2D c = Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2)
		+ Vector2D(sdlutils().rand().nextInt(-100, 101),
			sdlutils().rand().nextInt(-100, 101));

	// Devolverlo nomalizado 
	return (c - posAst).normalize() * speed;
}

void AsteroidsSystem::createSon(Transform* father, int newGen) {
	
}