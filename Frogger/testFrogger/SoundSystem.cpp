#include "SoundSystem.h"

SoundSystem::SoundSystem()
{
	music.openFromFile("Media/Music/sound-frogger-theme.flac");
	music.setRelativeToListener(false);
	music.setLoop(true);

	hopBuffer.loadFromFile("Media/Music/sound-frogger-hop.wav");
	hopSnd.setBuffer(hopBuffer);

	plunkBuffer.loadFromFile("Media/Music/sound-frogger-plunk.wav");
	plunkSnd.setBuffer(plunkBuffer);

	squashBuffer.loadFromFile("Media/Music/sound-frogger-squash.wav");
	squashSnd.setBuffer(squashBuffer);
}

void SoundSystem::playSound(Sound type)
{
	switch (type)
	{
	case SoundSystem::hop: hopSnd.play();
		break;
	case SoundSystem::plunk: plunkSnd.play();
		break;
	case SoundSystem::squash: squashSnd.play();
		break;
	default:
		break;
	}
}