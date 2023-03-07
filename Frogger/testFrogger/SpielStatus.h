
#include "Spiel.h"
#include "Welt.h"
#include "Spieler.h"

#include <SFML/Graphics.hpp>

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void		draw() override;
	virtual bool		update(sf::Time dt) override;
	virtual bool		handleEvent(const sf::Event& event) override;

private:
	World				world;
	Player& player;

};

