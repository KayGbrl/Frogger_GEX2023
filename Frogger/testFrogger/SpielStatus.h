#include "Spiel.h"
#include "Welt.h"
#include "StatenCheck.h"
#include "ElementErkennung.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

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
