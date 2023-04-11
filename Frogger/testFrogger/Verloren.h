#pragma once

#include "Spiel.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>

class GameOverState : public State
{
public:

	GameOverState(StateStack& stack, Context context);

	virtual void			draw() override;
	virtual bool			aktualisieren(sf::Time dt) override;
	virtual bool			ereiknissHandeln(const sf::Event& event) override;

private:
	sf::Text				verlorenText_;
	sf::Time				abgelaufeneZeit_;
};

