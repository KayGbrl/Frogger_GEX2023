#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include <vector>

using Frame = sf::IntRect;

class Animation
{
public:
	explicit 				Animation(bool repeat = true);

	void					gameFrame(Frame frame);
	void					gameFrameSet(std::vector<Frame> frames);
	void 					gameSetDuration(sf::Time duration);
	sf::Time 				gameGetDuration() const;

	void 					gameRepeating(bool flag);
	bool 					gameIsRepeating() const;

	void 					restart();
	bool 					isFinished() const;

	Frame					gameCurrentFrame() const;

	Frame 					update(sf::Time dt);

private:
	std::vector<Frame>		frames_;
	std::size_t 			currentFrame_;
	sf::Time 				duration_;
	sf::Time 				elapsedTime_;
	bool 					repeat_;
};

