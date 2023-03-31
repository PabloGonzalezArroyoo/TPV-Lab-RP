#pragma once
#include "../ecs/System.h"

#include "../components/FighterCtrl.h"
#include "../components/Follow.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../components/Health.h"
#include "../components/Transform.h"

class AsteroidsSystem : public System {
public:
	constexpr static sysId_type id = _sys_ASTEROIDS;

	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	virtual void receive(const Message& m) override;

	// Inicializar el sistema, etc.
	virtual void initSystem() override;

	// Si el juego est� parado no hacer nada, en otro caso mover los asteroides como
	// en la pr�ctica 1 y generar 1 asteroide nuevo cada 5 segundos (aparte
	// de los 10 al principio de cada ronda).
	virtual void update() override;

private:
	// Para gestionar el mensaje de que ha habido un choque de un asteroide con una
	// bala. Desactivar el asteroide �a� y crear 2 asteroides como en la pr�ctica 1,
	// y si no hay m�s asteroides enviar un mensaje correspondiente.
	void onCollision_AsteroidBullet(Entity* a);

	// Para gestionar el mensaje de que ha acabado la ronda. Desactivar todos los
	// asteroides, y desactivar el sistema.
	void onRoundOver();

	// Para gestionar el mensaje de que ha empezado una ronda. Activar el sistema y
	// a�adir los asteroides iniciales (como en la pr�ctica 1).
	void onRoundStart();

	void createAsteroids(int n);
	Vector2D randomPos();
	Vector2D randomVel(Vector2D posAst);
	void createSon(Transform* father, int newGen);

	bool disableOnExit(Transform* tr);
	void setFollowVelocity(Transform* myTr, Transform* plTr, float randomSpeed);

	// El n�mero actual de asteroides en el juego (recuerda que no puede superar un
	// l�mite)
	int numOfAsteroids_;

	float frameTime, startTime;
};
