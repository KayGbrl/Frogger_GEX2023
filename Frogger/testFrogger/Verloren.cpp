#include "Verloren.h"
#include "Bewegung.h"
#include "Elemente.h"
#include "Spiel.h"
#include "Leeren.h"

#include "SpriteElemente.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


GameOverState::GameOverState(StateStack& stack, Context context)
	: State(stack, context)
	, gameOverText()
	, elapsedTime(sf::Time::Zero)
{
	sf::Font& font = context.fonts->get(FontID::Main);
	sf::Vector2f windowSize(context.window->getSize());

	gameOverText.setFont(font);
	if (context.player->aufgabeBekommen() == Player::MissionStatus::Failure)
		gameOverText.setString("Game over!");
	else
		gameOverText.setString("You Won!");

	gameOverText.setCharacterSize(50);
	centerOrigin(gameOverText);
	gameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;

	if (context.player->aufgabeBekommen() == Player::MissionStatus::Failure)
		backgroundShape.setFillColor(sf::Color(255, 0, 0, 150));
	else
		backgroundShape.setFillColor(sf::Color(0, 255, 0, 150));

	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(gameOverText);
}

bool GameOverState::update(sf::Time dt)
{
	if (elapsedTime >= sf::seconds(3)) {
		stack->statusleeren();
		stack->statusDrucken(StateID::Title);
	}
	elapsedTime += dt;

	return false;
}

bool GameOverState::handleEvent(const sf::Event& event)
{
	return false;
}
