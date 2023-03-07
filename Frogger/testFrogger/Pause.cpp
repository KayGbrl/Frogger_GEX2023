#include "Pause.h"
#include "Werkzeug.h"
#include "Elemente.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
	, backgroundSprite()
	, pausedText()
	, instructionText()
{
	sf::Font& font = context.fonts->get(FontID::Main);
	sf::Vector2f viewSize = context.window->getView().getSize();

	pausedText.setFont(font);
	pausedText.setString("Game Paused");
	pausedText.setCharacterSize(30);
	centerOrigin(pausedText);
	pausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	instructionText.setFont(font);
	instructionText.setString("Escape to go to main Menu");
	instructionText.setCharacterSize(20);
	centerOrigin(instructionText);
	instructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;

	backgroundShape.setFillColor(sf::Color(0, 0, 0, 70));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(pausedText);
	window.draw(instructionText);
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;
	if (event.key.code == sf::Keyboard::P)
	{
		requestStackPop();
	}
	if (event.key.code == sf::Keyboard::Escape)
	{
		requestStateClear();
		requestStackPush(StateID::Menu);
	}
	return false;
}

