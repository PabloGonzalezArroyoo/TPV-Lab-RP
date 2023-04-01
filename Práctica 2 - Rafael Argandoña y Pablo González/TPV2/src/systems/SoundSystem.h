#pragma once
#include "../ecs/System.h"

class SoundSystem :  public System {
public:
	constexpr static sysId_type id = _sys_SOUND;

	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	virtual void receive(const Message& m) override;

private:
	// Metodos que reproducen o paran sonidos
	void reproduceSFX(SoundEffect* s);
	void reproduceMusic(Music* m, bool loop);
	void stopMusic(Music* m);

	// Variables de tiempo
	float frameTime, startTime;
};

