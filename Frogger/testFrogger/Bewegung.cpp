#include "Bewegung.h"
#include "Ausloser.h"
#include "Frogger.h"
#include "SoundSystem.h"
#include "Arten.h"

#include <algorithm>


Kommando::Kommando()
	: action()
	, category(Category::None)
{}

Player::Player()
	: missionsZiel(MissionStatus::Running)
{
	tastenSchlag();
	actionMachen();

	for (auto& pair : bewegungMachen) {
		pair.second.category = Category::Frogger;
	}
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto found = tastenBelegung.find(event.key.code);
		if (found != tastenBelegung.end() && !echtzeit(found->second))
			commands.push(bewegungMachen[found->second]);
	}
}

void Player::eingabe(CommandQueue& commands)
{
	for (auto pair : tastenBelegung) {

		if (sf::Keyboard::isKeyPressed(pair.first) && echtzeit(pair.second))
			commands.push(bewegungMachen[pair.second]);
	}
}

void Player::aufgabeGeben(MissionStatus status)
{
	missionsZiel = status;
}

Player::MissionStatus Player::aufgabeBekommen() const
{
	return missionsZiel;
}

void Player::tastenSchlag() {
	tastenBelegung[sf::Keyboard::Left] = Action::MoveLeft;
	tastenBelegung[sf::Keyboard::Right] = Action::MoveRight;
	tastenBelegung[sf::Keyboard::Up] = Action::MoveUp;
	tastenBelegung[sf::Keyboard::Down] = Action::MoveDown;

	tastenBelegung[sf::Keyboard::A] = Action::MoveLeft;
	tastenBelegung[sf::Keyboard::D] = Action::MoveRight;
	tastenBelegung[sf::Keyboard::W] = Action::MoveUp;
	tastenBelegung[sf::Keyboard::S] = Action::MoveDown;
}


void Player::actionMachen()
{
	bewegungMachen[Action::MoveLeft].action = derivedAction<Frogger>(
		[](Frogger& a, sf::Time dt) {
			a.hop(Arten::Direction::Links);
		});

	bewegungMachen[Action::MoveRight].action = derivedAction<Frogger>(
		[](Frogger& a, sf::Time dt) {
			a.hop(Arten::Direction::Rechts);
		});

	bewegungMachen[Action::MoveUp].action = derivedAction<Frogger>(
		[](Frogger& a, sf::Time dt) {
			a.hop(Arten::Direction::Oben);
		});

	bewegungMachen[Action::MoveDown].action = derivedAction<Frogger>(
		[](Frogger& a, sf::Time dt) {
			a.hop(Arten::Direction::Unten);
		});
}

bool Player::echtzeit(Action action)
{
	switch (action)
	{
	case Action::MoveLeft:
	case Action::MoveRight:
	case Action::MoveDown:
	case Action::MoveUp:
		return false;
	default:
		return false;
	}
}
