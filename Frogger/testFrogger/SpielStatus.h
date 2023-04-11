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
	virtual bool		aktualisieren(sf::Time dt) override;
	virtual bool		ereiknissHandeln(const sf::Event& event) override;

private:
	World				welt;
	Player& player;

};
