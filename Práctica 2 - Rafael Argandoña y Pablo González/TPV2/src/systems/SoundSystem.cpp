#include "SoundSystem.h"

void SoundSystem::receive(const Message& m) {
	switch (m.id) {
		case _m_PLAY_SOUND:
			reproduceSFX(m._sound_data.sound);
		break;

		case _m_PLAY_MUSIC:
			reproduceMusic(m._music_data.music);
		break;

		case _m_STOP_MUSIC:
			stopMusic(m._music_data.music);
			break;
	}
}

void SoundSystem::initSystem() {

}

void SoundSystem::reproduceSFX(SoundEffect* s) {
	s->play();
}

void SoundSystem::reproduceMusic(Music* m) {
	m->play();
}

void SoundSystem::stopMusic(Music* m) {
	m->haltMusic();
}