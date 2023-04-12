#include "SpielStatus.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Leeren.h"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, world(*context.window, *context.fonts)
	, player(*context.player)
{}

void GameState::draw()
{
	world.draw();
}

bool GameState::update(sf::Time dt)
{
	world.update(dt);

	if (!world.playerAlive()) {
		player.aufgabeGeben(Player::MissionStatus::Failure);
		erwarteStapelDrucken(StateID::SpielVerloren);
	}
	else if (world.reachedEnd()) {
		player.aufgabeGeben(Player::MissionStatus::Success);
		erwarteStapelDrucken(StateID::SpielVerloren);
	}

	CommandQueue& commands = world.getCommands();
	player.eingabe(commands);

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	CommandQueue& commands = world.getCommands();
	player.handleEvent(event, commands);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
		erwarteStapelDrucken(StateID::Pause);

	return true;
}