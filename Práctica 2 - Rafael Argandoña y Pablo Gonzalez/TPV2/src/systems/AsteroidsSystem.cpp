#include "AsteroidsSystem.h"
#include "../ecs/Manager.h"

void AsteroidsSystem::initSystem() {
	frameTime = 0.0f;
	startTime = sdlutils().currRealTime();
	numOfAsteroids_ = 0;
	onRoundStart();
}

void AsteroidsSystem::update() {
	if (active_) {
		// Guardar el tiempo actual
		frameTime = sdlutils().currRealTime() - startTime;

		// Si es momento de crear un asteroide y no sobrepaso el limite
		if (frameTime >= AST_FREQUENCY && numOfAsteroids_ < LIMIT_ASTEROIDS) {
			// Crear uno
			createAsteroids(1);

			// Resetear startTime
			startTime = sdlutils().currRealTime();
		}
	}	
}

void AsteroidsSystem::onCollision_AsteroidBullet(Entity* a) {
	mngr->setAlive(a, false);
	int gen = mngr->getComponent<Generations>(a)->getGenerations();
	if (gen >= 2) {
		createSon(mngr->getComponent<Transform>(a), gen-1);
		createSon(mngr->getComponent<Transform>(a), gen-1);
	}
	numOfAsteroids_--;
}

void AsteroidsSystem::onRoundOver() {
	mngr->removeEntities(_grp_ASTEROIDS);
}

void AsteroidsSystem::onRoundStart() {
	active_ = true;
	createAsteroids(10);
}

void AsteroidsSystem::createAsteroids(int n) {
	numOfAsteroids_ += n;
	for (int i = 0; i < n; i++) {
		// A�adir la entidad al manager y a su grupo
		Entity* ast = mngr->addEntity(_grp_ASTEROIDS);

		// C�lculo de generaciones y a�adir componente
		int gen = SDLUtils::instance()->rand().nextInt(1, 4);
		mngr->addComponent<Generations>(ast, gen);

		// Calculamos su posicion y velocidad y las aplicamos al a�adir el transform del componente
		Vector2D pos = randomPos();
		Vector2D vel = randomVel(pos);
		int dimensions = ASTEROIDS_DIMENSIONS + 5.0f * gen;
		mngr->addComponent<Transform>(ast, pos, vel, dimensions, dimensions);

		// Tipo B -> tendr�n animaci�n espec�fica y el componente follow para seguir al personaje
		if (SDLUtils::instance()->rand().nextInt(0, 10) < 3) {
			mngr->addComponent<FramedImage>(ast, &sdlutils().images().at(ASTEROID_B), ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
			mngr->addComponent<Follow>(ast);
		}
		// Tipo A -> solo tendr�n una animaci�n espec�fica
		else {
			mngr->addComponent<FramedImage>(ast, &sdlutils().images().at(ASTEROID_A), ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
		}

		// A�adir el componente de desactivar al salir de la pantalla
		mngr->addComponent<DisableOnExit>(ast);
	}
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
	if (numOfAsteroids_ + 1 < LIMIT_ASTEROIDS) {
		numOfAsteroids_++;

		auto r = sdlutils().rand().nextInt(0, 360);
		auto pos = father->getPosition() + father->getVelocity().rotate(r)
			* 2 * max(father->getWidth(), father->getHeight());
		auto vel = father->getVelocity().rotate(r) * 1.1f;

		Entity* ast = mngr->addEntity();
		int dimensions = ASTEROIDS_DIMENSIONS + 5.0f * newGen;
		mngr->addComponent<Transform>(ast, pos, vel, dimensions, dimensions);
		mngr->addComponent<Generations>(ast, newGen);
		mngr->addComponent<DisableOnExit>(ast);

		if (sdlutils().rand().nextInt(0, 10) < 3) {
			mngr->addComponent<FramedImage>(ast, &sdlutils().images().at(ASTEROID_B), ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
			mngr->addComponent<Follow>(ast);
		}

		else {
			mngr->addComponent<FramedImage>(ast, &sdlutils().images().at(ASTEROID_A), ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
		}
	}
}