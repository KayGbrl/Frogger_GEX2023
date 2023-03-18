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
		player.setMissionStatus(Player::MissionStatus::Failure);
		requestStackPush(StateID::GameOverState);
	}
	else if (world.reachedEnd()) {
		player.setMissionStatus(Player::MissionStatus::Success);
		requestStackPush(StateID::GameOverState);
	}

	CommandQueue& commands = world.getCommands();
	player.handleRealTimeInput(commands);

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	CommandQueue& commands = world.getCommands();
	player.handleEvent(event, commands);

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
		requestStackPush(StateID::Pause);

	return true;
}