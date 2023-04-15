#include "SoundSystem.h"

// Recibir mensajes
void SoundSystem::receive(const Message& m) {
	switch (m.id) {
		// Reproducir un sonido
		case _m_PLAY_SOUND:
			reproduceSFX(m._sound_data.sound);
		break;

		// Reproducir música
		case _m_PLAY_MUSIC:
			reproduceMusic(m._music_data.music, m._music_data.loop == 0);
		break;

		// Parar música
		case _m_STOP_MUSIC:
			stopMusic(m._music_data.music);
			break;
	}
}

// Reproduce un efecto de sonido
void SoundSystem::reproduceSFX(SoundEffect* s) {
	s->play();
}

// Reproduce una cancion en bucle o no
void SoundSystem::reproduceMusic(Music* m, bool loop) {
	if (loop) m->play(0);
	else m->play();
}

// Para una canción dada
void SoundSystem::stopMusic(Music* m) {
	m->haltMusic();
}