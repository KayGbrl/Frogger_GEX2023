#pragma once

#include "SFML\Audio.hpp"
#include "SFML\System.hpp"

class SoundSystem
{
public:
	inline static SoundSystem& Instance() {
		static SoundSystem theSS;
		return theSS;
	}
	enum Sound { hop, plunk, squash };

	void playMusic() { music.play(); }
	void playSound(Sound type);

private:
	SoundSystem();
	SoundSystem(SoundSystem const&);
	SoundSystem& operator= (SoundSystem const&);
	~SoundSystem() {}

	sf::Music music;

	sf::SoundBuffer hopBuffer;
	sf::Sound hopSnd;

	sf::SoundBuffer plunkBuffer;
	sf::Sound plunkSnd;

	sf::SoundBuffer squashBuffer;
	sf::Sound squashSnd;
};