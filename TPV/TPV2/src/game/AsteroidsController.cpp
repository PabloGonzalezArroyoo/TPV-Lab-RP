#include "AsteroidsController.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

AsteroidsController::AsteroidsController(Manager* _mng, Game* g) : mng(_mng), game(g), numAst(0), 
																	startTime(SDL_GetTicks()), frameTime(0){ }

// TO-DO
void AsteroidsController::createAsteroids(int n) {
	for (int i = 0; i < n; i++) {
		Entity* asteroid = mng->addEntity(_grp_ASTEROIDS);
		
		// Generaciones
		int gen = SDLUtils::instance()->rand().nextInt(1, 4);
		asteroid->addComponent<Generations>(gen);

		// Calculamos su posicion y velocidad
		Vector2D pos = randomPos();
		Vector2D vel = randomVel(pos);
		int dimensions = ASTEROIDS_DIMENSIONS + 5.0f * gen;
		asteroid->addComponent<Transform>(pos, vel, dimensions, dimensions);

		// Tipo B
		if (SDLUtils::instance()->rand().nextInt(0, 10) < 3) {
			asteroid->addComponent<FramedImage>(game->getTexture(ASTEROIDS_GOLD), ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
			asteroid->addComponent<Follow>();
		}
		// Tipo A
		else {
			asteroid->addComponent<FramedImage>(game->getTexture(ASTEROIDS_SILVER), ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
		}
		asteroid->addComponent<DisableOnExit>();
	}
}

void AsteroidsController::addAsteroidsFrequently() {
	frameTime = SDL_GetTicks() - startTime;
	if (frameTime >= 5000) {
		createAsteroids(1);
		startTime = SDL_GetTicks();
	}
}

void AsteroidsController::destroyAllAsteroids() {
	auto ents = mng->getEntities(_grp_ASTEROIDS);
	for (Entity* e : ents) e->setAlive(false);
}

void AsteroidsController::OnCollision(Entity* a) {
	a->setAlive(false);
	int gen = a->getComponent<Generations>()->getGenerations();
	if (gen >= 2) {
		createSon(a->getComponent<Transform>(), gen - 1);
		createSon(a->getComponent<Transform>(), gen - 1);
	}
}

Vector2D AsteroidsController::randomPos() {
	int x = 0, y = 0;

	// Lado de la pantalla
	switch(SDLUtils::instance()->rand().nextInt(0, 4)) {
	// Arriba
	case 0:
		y = SDLUtils::instance()->rand().nextInt(0,10);
		x = SDLUtils::instance()->rand().nextInt(0, WIN_WIDTH);
		break;
	// Izquierda
	case 1:
		y = SDLUtils::instance()->rand().nextInt(0, WIN_HEIGHT);
		x = SDLUtils::instance()->rand().nextInt(0, 10);
		break;
	// Derecha
	case 2:
		y = SDLUtils::instance()->rand().nextInt(0, WIN_HEIGHT);
		x = SDLUtils::instance()->rand().nextInt(WIN_WIDTH - 10, WIN_WIDTH);
		break;
	// Abajo
	case 3:
		y = SDLUtils::instance()->rand().nextInt(WIN_HEIGHT - 10, WIN_HEIGHT);
		x = SDLUtils::instance()->rand().nextInt(0, WIN_WIDTH);
		break;
	}

	return Vector2D(x, y);
}

Vector2D AsteroidsController::randomVel(Vector2D posAst) {
	float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;
	Vector2D c = Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2) +
		Vector2D(SDLUtils::instance()->rand().nextInt(-100, 101), SDLUtils::instance()->rand().nextInt(-100, 101));
	
	return (c - posAst).normalize() * speed;
}

void AsteroidsController::createSon(Transform* father, int newGen) {
	auto r = SDLUtils::instance()->rand().nextInt(0, 360);
	auto pos = father->getPosition() + father->getVelocity().rotate(r)
		* 2 * max(father->getWidth(), father->getHeight());
	auto vel = father->getVelocity().rotate(r) * 1.1f;

	Entity* ast = mng->addEntity(_grp_ASTEROIDS);
	int dimensions = ASTEROIDS_DIMENSIONS + 5.0f * newGen;
	ast->addComponent<Transform>(pos, vel, dimensions, dimensions);
	ast->addComponent<Generations>(newGen);
	ast->addComponent<DisableOnExit>();

	// Tipo B
	if (SDLUtils::instance()->rand().nextInt(0, 10) < 3) {
		ast->addComponent<FramedImage>(game->getTexture(ASTEROIDS_GOLD), ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
		ast->addComponent<Follow>();
	}
	// Tipo A
	else {
		ast->addComponent<FramedImage>(game->getTexture(ASTEROIDS_SILVER), ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
	}
}