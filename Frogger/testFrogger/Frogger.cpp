#include "Frogger.h"
#include "Arten.h"
#include "Elemente.h"
#include "ElementErkennung.h"
#include "JsonFrameParser.h"
#include "DataTables.h"
#include "SoundSystem.h"
#include "StatenCheck.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


namespace
{
	const std::map<Arten::Type, Karachtere> TABLE = artenData();
}

Frogger::Frogger(const TextureHolder_t& textures, const FontHolder_t& fonts)
	: Arten(textures, fonts)
	, state_(SpeilStatus::Stehenhoch)
	, sprite_(textures.get(TABLE.at(Arten::Type::Frogger).texturen))
	, direction_(Direction::Up)
	, directionIndex_(0)
	, stateCountdown_(sf::Time::Zero)
	, respawnPosition_(240.f, 580.f)
	, livesLeft_(3)
	, isMarkedForRemoval_(false)
	, hasFroggerFilledSlots_(false)
{
	for (auto a : TABLE.at(Arten::Type::Frogger).animationen)
	{
		animations_[a.first] = a.second;
	}

	sprite_.setTextureRect(animations_[Arten::SpeilStatus::Stehenhoch].gameCurrentFrame());
	zentrierterPunkt(sprite_);

	GeschwindigkeitSetzen(0.f, 0.f);
}

unsigned int Frogger::getCategory() const
{
	return Category::Frogger;
}

sf::FloatRect Frogger::getBoundingRect() const
{
	auto box = getWorldTransform().transformRect(sprite_.getGlobalBounds());
	box.width -= 10; 
	box.left += 5;
	box.top += 5;
	box.height -= 10;
	return box;
}

float Frogger::getMaxSpeed() const
{
	return 0.f;
}

bool Frogger::zumEntfernen() const
{
	return isMarkedForRemoval_;
}

void Frogger::setHasFroggerFilledSlots()
{
	hasFroggerFilledSlots_ = true;
}

bool Frogger::hasFroggerFilledSlots() const
{
	return hasFroggerFilledSlots_;
}

void Frogger::setIsWinningSpotTaken()
{
	isWinningSpotTaken_ = true;
}

void Frogger::setState(SpeilStatus state)
{
	if (state_ != state) {
		state_ = state;
		animations_[state_].restart();
	}
}

Frogger::SpeilStatus Frogger::getState() const
{
	return state_;
}

bool Frogger::isStruckByCar() const
{
	return isStruckByCar_;
}

void Frogger::setIsStruckByCar(bool b)
{
	isStruckByCar_ = b;
}

bool Frogger::isInRiver() const
{
	return isInRiver_;
}

void Frogger::setIsInRiver(bool b)
{
	isInRiver_ = b;
}

bool Frogger::isOnSwimmingNPC() const
{
	return isOnSwimmingNPC_;
}

void Frogger::playerOnSwimmingNPC(bool b)
{
	isOnSwimmingNPC_ = b;
}

void Frogger::resetPositionFlags()
{
	isStruckByCar_ = false;
	isInRiver_ = false;
	isOnSwimmingNPC_ = false;
	isWinningSpotTaken_ = false;
}

void Frogger::setStateCountdownToZero()
{
	stateCountdown_ = sf::Time::Zero;
}

sf::Time Frogger::getStateCountdown()
{
	return stateCountdown_;
}

int Frogger::getScore()
{
	return score_;
}

void Frogger::addScore(int score)
{
	score_ += score;
}

int Frogger::getLivesLeft()
{
	return livesLeft_;
}

void Frogger::deductLife()
{
	livesLeft_ -= 1;
}

void Frogger::hop(Arten::Direction direction)
{
	const float playerSpeedY = 40.f;
	const float playerSpeedX = 50.f;

	if (state_ == Arten::SpeilStatus::Tod)
		return;

	if (direction == Arten::Direction::Links) {
		setPosition(sf::Vector2f(getPosition().x - playerSpeedX, getPosition().y));
		setState(Frogger::SpeilStatus::Links);
	}
	else if (direction == Arten::Direction::Rechts) {
		setPosition(sf::Vector2f(getPosition().x + playerSpeedX, getPosition().y));
		setState(Frogger::SpeilStatus::Rechts);
	}
	else if (direction == Arten::Direction::Oben) {
		setPosition(sf::Vector2f(getPosition().x, getPosition().y - playerSpeedY));
		score_ += 10;
		setState(Frogger::SpeilStatus::Hoch);
	}
	else if (direction == Arten::Direction::Unten) {
		setPosition(sf::Vector2f(getPosition().x, getPosition().y + playerSpeedY));
		score_ -= 10;
		setState(Frogger::SpeilStatus::Runter);
	}
	setStateCountdownToZero();

	SoundSystem::Instance().playSound(SoundSystem::Sound::hop);
}

void Frogger::respawnFrogger()
{
	setState(Arten::SpeilStatus::Stehenhoch);
	setPosition(respawnPosition_);
	resetPositionFlags();
}


void Frogger::updateStates()
{
	const sf::Time SPRUNG = sf::milliseconds(100);
	const sf::Time TODESZEITPUNKT = sf::milliseconds(1200);

	if (state_ == Arten::SpeilStatus::Tod && stateCountdown_ > TODESZEITPUNKT) {
		livesLeft_ -= 1;
		if (livesLeft_ > 0)
			respawnFrogger();
	}
	else if (state_ == Arten::SpeilStatus::Links && (stateCountdown_ > SPRUNG)) {
		setState(Arten::SpeilStatus::Stehenlinks);
	}
	else if (state_ == Arten::SpeilStatus::Rechts && (stateCountdown_ > SPRUNG)) {
		setState(Arten::SpeilStatus::Stehenrechts);
	}
	else if (state_ == Arten::SpeilStatus::Hoch && (stateCountdown_ > SPRUNG)) {
		setState(Arten::SpeilStatus::Stehenhoch);
	}
	else if (state_ == Arten::SpeilStatus::Runter && (stateCountdown_ > SPRUNG)) {
		setState(Arten::SpeilStatus::Stehenrunter);
	}

	if (isStruckByCar_ || (isInRiver_ && !isOnSwimmingNPC_) || isWinningSpotTaken_) {
		setState(Arten::SpeilStatus::Tod);
		if (isInRiver_ && !isOnSwimmingNPC_)
			SoundSystem::Instance().playSound(SoundSystem::Sound::plunk);
		else if (isStruckByCar_)
			SoundSystem::Instance().playSound(SoundSystem::Sound::squash);
	}
}

void Frogger::aktuellesBild(sf::Time dt, CommandQueue& commands)
{
	stateCountdown_ += dt;
	updateStates();

	auto rec = animations_.at(state_).update(dt);

	move(geschwindigkeit * dt.asSeconds());

	sprite_.setTextureRect(rec);
	zentrierterPunkt(sprite_);
}

void Frogger::aktuellezeichnen(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

//Huaptmenu Funktionen
Menu::Menu(StateStack& stack, Context context)
	: State(stack, context)
	, optionen()
	, optionIndex(0)
{

	sf::Font& font = context.fonts->get(FontID::Main);

	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	zentrierterPunkt(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	optionen.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	zentrierterPunkt(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
	optionen.push_back(exitOption);

	updateOptionText();

}

void Menu::draw()
{
	auto& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(hintergrund);

	for (const auto& text : optionen) {
		window.draw(text);
	}
}

bool Menu::update(sf::Time dt)
{
	return true;
}

bool Menu::handleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{
		if (optionIndex == Play) {
			requestStackPop();
			requestStackPush(StateID::Game);
		}
		else if (optionIndex == Exit)
		{
			requestStackPop();
		}
	}
	else if (event.key.code == sf::Keyboard::Up)
	{
		if (optionIndex > 0)
			optionIndex--;
		else
			optionIndex = optionen.size() - 1;

		updateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		if (optionIndex < optionen.size() - 1)
			optionIndex++;
		else
			optionIndex = 0;

		updateOptionText();
	}

	return true;
}

void Menu::updateOptionText() {
	if (optionen.empty())
		return;

	for (auto& text : optionen)
		text.setFillColor(sf::Color::White);

	optionen[optionIndex].setFillColor(sf::Color::Blue);
}

//Pause Menu
Pause::Pause(StateStack& stack, Context context)
	: State(stack, context)
	, hintergrungSprite()
	, pauseText()
	, hilfeText()
{
	sf::Font& font = context.fonts->get(FontID::Main);
	sf::Vector2f viewSize = context.window->getView().getSize();

	pauseText.setFont(font);
	pauseText.setString("Game Paused");
	pauseText.setCharacterSize(30);
	zentrierterPunkt(pauseText);
	pauseText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	hilfeText.setFont(font);
	hilfeText.setString("Escape to go to main Menu");
	hilfeText.setCharacterSize(20);
	zentrierterPunkt(hilfeText);
	hilfeText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void Pause::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;

	backgroundShape.setFillColor(sf::Color(0, 0, 0, 70));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(pauseText);
	window.draw(hilfeText);
}

bool Pause::update(sf::Time dt)
{
	return false;
}

bool Pause::handleEvent(const sf::Event& event)
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

