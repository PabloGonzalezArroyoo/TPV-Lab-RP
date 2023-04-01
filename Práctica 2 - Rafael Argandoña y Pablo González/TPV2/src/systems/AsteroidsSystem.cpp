#include "AsteroidsSystem.h"
#include "../ecs/Manager.h"

// Recibir mensajes
void AsteroidsSystem::receive(const Message& m) {
	switch (m.id) {
		// Si ha colisionado un asteroide con una bala, llamar al método
		case _m_ASTEROID_COLLIDED:
			onCollision_AsteroidBullet(m.asteroid_collided_data.e);
			break;

		// Al acabar la ronda
		case _m_ROUND_OVER:
			onRoundOver();
			break;
	}
}

// Inicializar variables del sistema y llamar al inicio de la ronda
void AsteroidsSystem::initSystem() {
	// Inicializar variables
	frameTime = 0.0f;
	startTime = sdlutils().currRealTime();
	numOfAsteroids_ = 0;

	// Empezar ronda
	onRoundStart();
}

// Mover asteroides, crear nuevos cada 1 sec y comprobar victoria
void AsteroidsSystem::update() {
	// Guardar el tiempo actual
	frameTime = sdlutils().currRealTime() - startTime;

	// Si es momento de crear un asteroide y no sobrepaso el limite
	if (frameTime >= AST_FREQUENCY && numOfAsteroids_ < LIMIT_ASTEROIDS) {
		// Crear uno
		createAsteroids(1);

		// Resetear startTime
		startTime = sdlutils().currRealTime();
	}

	// Mover los asteroides
	vector<Entity*> entities = mngr->getEntities(_grp_ASTEROIDS);
	Transform* plTr = mngr->getComponent<Transform>(mngr->getHandler(_hdlr_FIGHTER));
	Transform* tr = nullptr;
	for (int i = 0; i < entities.size(); i++) {
		tr = mngr->getComponent<Transform>(entities[i]);

		// Si es un asteroide dorado, actualizar velocidad hacia el jugador
		if (mngr->hasComponent<Follow>(entities[i])) {
			setFollowVelocity(tr, plTr, mngr->getComponent<Follow>(entities[i])->getRandomSpeed());
		}

		// Aplicar
		tr->setPosition(tr->getPosition() + tr->getVelocity());

		// Deshabilitar si se sale de la pantalla
		if (disableOnExit(tr)) {
			mngr->setAlive(entities[i], false);
			numOfAsteroids_--;
		}
	}

	// Comprobar si se ha ganado
	if (numOfAsteroids_ <= 0) {
		Message m;
		m.id = _m_PLAYER_WINS;
		mngr->send(m, true);
	}
}

// Deshabilitar asterioide si se sale de la pantalla
bool AsteroidsSystem::disableOnExit(Transform* tr) {
	// Coger la posición
	Vector2D position = tr->getPosition();

	// Si se sale por algún lateral de la pantalla, desactivarlo
	return position.getX() < 0 - tr->getWidth() || position.getX() > WIN_WIDTH
		|| position.getY() < 0 - tr->getHeight() || position.getY() > WIN_HEIGHT;
}

// Settear velocidad hacia el jugador
void AsteroidsSystem::setFollowVelocity(Transform* myTr, Transform* plTr, float randomSpeed) {
	// Calculamos la nueva velocidad y le asignamos una rotación adecuada
	Vector2D newVel = (plTr->getPosition() - myTr->getPosition()).normalize() * randomSpeed;
	newVel.rotate(newVel.angle(plTr->getPosition() - myTr->getPosition()) > 0 ? 1.0f : -1.0f);

	// Asignamos la nueva velocidad
	myTr->setVelocity(newVel);
}

// Crear hijos al colisionar bala con asteroide y desactivar bala
void AsteroidsSystem::onCollision_AsteroidBullet(Entity* a) {
	// Desactivamos el asteroide
	mngr->setAlive(a, false);

	// Guardamos su generacion y si debemos crear asteroides hijos los creamos
	int gen = mngr->getComponent<Generations>(a)->getGenerations();
	if (gen >= 2) {
		createSon(mngr->getComponent<Transform>(a), gen-1);
		createSon(mngr->getComponent<Transform>(a), gen-1);
	}

	// Decrecemos el numero de asteroides
	numOfAsteroids_--;
}

// Al acabar la ronda
void AsteroidsSystem::onRoundOver() {
	// Al acabar la ronda eliminamos todos los asteroides y seteamos el numero a 0
	mngr->removeEntities(_grp_ASTEROIDS);
	numOfAsteroids_ = 0;

	// Llamamos a iniciar una nueva ronda
	onRoundStart();
}

// Al empezar la ronda
void AsteroidsSystem::onRoundStart() {
	// Creamos el numero inicial de asteroides por ronda
	createAsteroids(10);
}

// Crear asteroides
void AsteroidsSystem::createAsteroids(int n) {
	// Aumentamos el contador de asteroides
	numOfAsteroids_ += n;
	for (int i = 0; i < n; i++) {
		// Añadir la entidad al manager y a su grupo
		Entity* ast = mngr->addEntity(_grp_ASTEROIDS);

		// Cálculo de generaciones y añadir componente
		int gen = SDLUtils::instance()->rand().nextInt(1, 4);
		mngr->addComponent<Generations>(ast, gen);

		// Calculamos su posicion y velocidad y las aplicamos al añadir el transform del componente
		Vector2D pos = randomPos();
		Vector2D vel = randomVel(pos);
		int dimensions = ASTEROIDS_DIMENSIONS + 5.0f * gen;
		mngr->addComponent<Transform>(ast, pos, dimensions, dimensions, vel);

		// Tipo B -> tendrán animación específica y el componente follow para seguir al personaje
		if (SDLUtils::instance()->rand().nextInt(0, 10) < 3) {
			mngr->addComponent<FramedImage>(ast, &sdlutils().images().at(ASTEROID_B), ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
			mngr->addComponent<Follow>(ast);
		}
		// Tipo A -> solo tendrán una animación específica
		else {
			mngr->addComponent<FramedImage>(ast, &sdlutils().images().at(ASTEROID_A), ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
		}
	}
}

// Calcular una posición aleatoria
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
	// Si se puede crear un hijo sin superar el limite de asteroides
	if (numOfAsteroids_ + 1 < LIMIT_ASTEROIDS) {
		// Aumentamos el contador de asteroides
		numOfAsteroids_++;
		// Le asignamos una rotacion, una posicion y una velocidad aleatorias en función al padre 
		auto r = sdlutils().rand().nextInt(0, 360);
		auto pos = father->getPosition() + father->getVelocity().rotate(r)
			* 2 * max(father->getWidth(), father->getHeight());
		auto vel = father->getVelocity().rotate(r) * 1.1f;

		// Creamos el asteroide con sus componentes básicos
		Entity* ast = mngr->addEntity(_grp_ASTEROIDS);
		int dimensions = ASTEROIDS_DIMENSIONS + 5.0f * newGen;
		mngr->addComponent<Transform>(ast, pos, dimensions, dimensions, vel);
		mngr->addComponent<Generations>(ast, newGen);

		// Crear un asteroide dorado (con componente Follow) si un aletorio es menor que 3
		if (sdlutils().rand().nextInt(0, 10) < 3) {
			mngr->addComponent<FramedImage>(ast, &sdlutils().images().at(ASTEROID_B),
				ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
			mngr->addComponent<Follow>(ast);
		}
		// Crear un asteroide plateado (sin componente Follow)
		else {
			mngr->addComponent<FramedImage>(ast, &sdlutils().images().at(ASTEROID_A), 
				ASTEROIDS_FRAME_WIDTH, ASTEROIDS_FRAME_HEIGHT, ASTEROIDS_ROWS, ASTEROIDS_COLS);
		}
	}
}