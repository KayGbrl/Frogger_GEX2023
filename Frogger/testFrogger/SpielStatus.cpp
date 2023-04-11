#include "SpielStatus.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Leeren.h"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, welt(*context.window, *context.fonts)
	, player(*context.player)
{}

void GameState::draw()
{
	welt.draw();
}

bool GameState::aktualisieren(sf::Time dt)
{
	welt.update(dt);

	if (!welt.playerAlive()) {
		player.aufgabeGeben(Player::MissionStatus::Failure);
		anordnungDrucken(StateID::GameOverState);
	}
	else if (welt.reachedEnd()) {
		player.aufgabeGeben(Player::MissionStatus::Success);
		anordnungDrucken(StateID::GameOverState);
	}

	CommandQueue& commands = welt.getCommands();
	player.eingabe(commands);

	return true;
}

bool GameState::ereiknissHandeln(const sf::Event& event)
{
	CommandQueue& commands = welt.getCommands();
	player.handleEvent(event, commands);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
		anordnungDrucken(StateID::Pause);

	return true;
}