
#pragma once

#include "Spiel.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class PauseState :
	public State
{
public:
	PauseState(StateStack& stack, Context context);

	virtual void		draw() override;
	virtual bool		update(sf::Time dt) override;
	virtual bool		handleEvent(const sf::Event& event) override;

private:
	sf::Sprite			backgroundSprite;
	sf::Text			pausedText;
	sf::Text			instructionText;

};

