#include "AsteroidsController.h"
#include "../sdlutils/SDLUtils.h"
#include "Game.h"

// Constructora
AsteroidsController::AsteroidsController(Manager* _mng, Game* g) : mng(_mng), game(g), numAst(0), 
					startTime(sdlutils().currRealTime()), frameTime(0){ }

// Crear n asteroides
void AsteroidsController::createAsteroids(int n) {
	// Añadir al contador ese número de asteroides
	numAst += n;

	// Crear n asteroides
	for (int i = 0; i < n; i++) {
		// Añadir la entidad al manager y a su grupo
		Entity* asteroid = mng->addEntity(_grp_ASTEROIDS);
		
		// Cálculo de generaciones y añadir componente
		int gen = SDLUtils::instance()->rand().nextInt(1, 4);
		asteroid->addComponent<Generations>(gen);

		// Calculamos su posicion y velocidad y las aplicamos al añadir el transform del componente
		Vector2D pos = randomPos();
		Vector2D vel = randomVel(pos);
		int dimensions = ASTEROIDS_DIMENSIONS + 5.0f * gen;
		asteroid->addComponent<Transform>(pos, vel, dimensions, dimensions);

		// Tipo B -> tendrán animación específica y el componente follow para seguir al personaje
		if (SDLUtils::instance()->rand().nextInt(0, 10) < 3) {
			asteroid->addComponent<FramedImage>(&sdlutils().images().at(ASTEROID_B), ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
			asteroid->addComponent<Follow>();
		}
		// Tipo A -> solo tendrán una animación específica
		else {
			asteroid->addComponent<FramedImage>(&sdlutils().images().at(ASTEROID_A), ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
		}

		// Añadir el componente de desactivar al salir de la pantalla
		asteroid->addComponent<DisableOnExit>();
	}
}

// Añade asteroides al juego cada cierto tiempo
void AsteroidsController::addAsteroidsFrequently() {
	// Guardar el tiempo actual
	frameTime = SDLUtils::instance()->currRealTime() - startTime;

	// Si es momento de crear un asteroide y no sobrepaso el limite
	if (frameTime >= AST_FREQUENCY && numAst < LIMIT_ASTEROIDS) {
		// Crear uno
		createAsteroids(1);

		// Resetear startTime
		startTime = SDLUtils::instance()->currRealTime();
	}
}

// Destruye todos los asteroides del juego
void AsteroidsController::destroyAllAsteroids() {
	// Marcar que no hay asteroides
	numAst = 0;

	// Coger todas las entidades de los asteroides y marcar alive = false (se borrarán en el refresh)
	auto ents = mng->getEntities(_grp_ASTEROIDS);
	for (Entity* e : ents) e->setAlive(false);
}

// Destruye el objeto recibido y genera dos hijos si es necesario
void AsteroidsController::OnCollision(Entity* a) {
	// Marcamos el objeto para eliminarlo
	a->setAlive(false);
	// Nos guardamos el numero de generación del asteroide
	int gen = a->getComponent<Generations>()->getGenerations();
	// Si es superior a 1 creamos los 2 asteroides hijos
	if (gen >= 1) {
		createSon(a->getComponent<Transform>(), gen - 1);
		createSon(a->getComponent<Transform>(), gen - 1);
	}

	// Restar el asteroide eliminado
	numAst--;
}

// Calcular una posición aleatoria
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

// Calcular una velocidad aleatoria
Vector2D AsteroidsController::randomVel(Vector2D posAst) {
	// Calcular un aleatorio
	float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;

	// Calcular el vector
	Vector2D c = Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2)
		+ Vector2D(sdlutils().rand().nextInt(-100, 101), 
			sdlutils().rand().nextInt(-100, 101));
	
	// Devolverlo nomalizado 
	return (c - posAst).normalize() * speed;
}

// Crear asteroide hijo a partir de uno padre
void AsteroidsController::createSon(Transform* father, int newGen) {
	// Si no me paso de mi limite de asteroides
	if (numAst + 1 < LIMIT_ASTEROIDS) {
		// Aumento el numero de asteroides
		numAst++;
		// Generamos una posicion y una velocidad aleatorias en relación a la del padre
		auto r = SDLUtils::instance()->rand().nextInt(0, 360);
		auto pos = father->getPosition() + father->getVelocity().rotate(r)
			* 2 * max(father->getWidth(), father->getHeight());
		auto vel = father->getVelocity().rotate(r) * 1.1f;

		// Añadir la entidad al manager y al grupo junto a sus componentes
		Entity* ast = mng->addEntity(_grp_ASTEROIDS);
		int dimensions = ASTEROIDS_DIMENSIONS + 5.0f * newGen;
		ast->addComponent<Transform>(pos, vel, dimensions, dimensions);
		ast->addComponent<Generations>(newGen);
		ast->addComponent<DisableOnExit>();

		// Tipo B -> tendrán animación específica y el componente follow para seguir al personaje
		if (SDLUtils::instance()->rand().nextInt(0, 10) < 3) {
			ast->addComponent<FramedImage>(&sdlutils().images().at(ASTEROID_B), ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
			ast->addComponent<Follow>();
		}
		// Tipo A -> solo tendrán una animación específica
		else {
			ast->addComponent<FramedImage>(&sdlutils().images().at(ASTEROID_A), ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
		}
	}
}