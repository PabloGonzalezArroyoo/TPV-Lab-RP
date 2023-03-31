#pragma once
#include "../ecs/System.h"

class SoundSystem :  public System {
public:
	constexpr static sysId_type id = _sys_SOUND;

	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	virtual void receive(const Message& m) override;

	// Inicializar el sistema, etc.
	virtual void initSystem() override;

private:
	void reproduceSFX(SoundEffect* s);

	void reproduceMusic(Music* m);

	void stopMusic(Music* m);

	float frameTime, startTime;
};

