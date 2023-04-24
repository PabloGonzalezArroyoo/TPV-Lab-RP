#pragma once
#include "../ecs/System.h"

#include "../components/FighterCtrl.h"
#include "../components/Follow.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../components/Health.h"
#include "../components/Transform.h"

class GameCtrlSystem : public System {
public:
	constexpr static sysId_type id = _sys_GAME_CTRL;

	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	void receive(const Message& m) override;

	// Inicializar el sistema, etc.
	void initSystem() override;

private:
	// Para gestionar el mensaje de que ha habido un choque entre el fighter y un
	// un asteroide. Tiene que avisar que ha acabado la ronda, quitar una vida
	// al fighter, y si no hay m�s vidas avisar que ha acabado el juego (y quien
	// es el ganador).
	void onCollision_FighterAsteroid();

	// Para gestionar el mensaje de que no hay m�s asteroides. Tiene que avisar que
	// ha acabado la ronda y adem�s que ha acabado el juego (y quien es el ganador)
	void onAsteroidsExtinction();

	void onMultiplayerWin();
	void onMultiplayerLose();

	WINNER winner;
	STATE state; // El estado actual del juego (en lugar del componente State)
	Game* game;
};