#include "Frogger.h"
#include "Arten.h"
#include "Elemente.h"
#include "ElementErkennung.h"
#include "JsonFrameParser.h"
#include "Werkzeug.h"
#include "DataTables.h"
#include "SoundSystem.h"
#include "StatenCheck.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


namespace
{
	const std::map<Arten::Type, ActorData> TABLE = initializeActorData();
}

Frogger::Frogger(const TextureHolder_t& textures, const FontHolder_t& fonts)
	: Arten(textures, fonts)
	, state_(State::IdleUp)
	, sprite_(textures.get(TABLE.at(Arten::Type::Frogger).texture))
	, direction_(Direction::Up)
	, directionIndex_(0)
	, stateCountdown_(sf::Time::Zero)
	, respawnPosition_(240.f, 580.f)
	, livesLeft_(3)
	, isMarkedForRemoval_(false)
	, hasFroggerFilledSlots_(false)
{
	for (auto a : TABLE.at(Arten::Type::Frogger).animations)
	{
		animations_[a.first] = a.second;
	}

	sprite_.setTextureRect(animations_[Arten::State::IdleUp].gameCurrentFrame());
	centerOrigin(sprite_);

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

bool Frogger::isMarkedForRemoval() const
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

void Frogger::setState(State state)
{
	if (state_ != state) {
		state_ = state;
		animations_[state_].restart();
	}
}

Frogger::State Frogger::getState() const
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

	if (state_ == Arten::State::Death)
		return;

	if (direction == Arten::Direction::Left) {
		setPosition(sf::Vector2f(getPosition().x - playerSpeedX, getPosition().y));
		setState(Frogger::State::JumpLeft);
	}
	else if (direction == Arten::Direction::Right) {
		setPosition(sf::Vector2f(getPosition().x + playerSpeedX, getPosition().y));
		setState(Frogger::State::JumpRight);
	}
	else if (direction == Arten::Direction::Up) {
		setPosition(sf::Vector2f(getPosition().x, getPosition().y - playerSpeedY));
		score_ += 10;
		setState(Frogger::State::JumpUp);
	}
	else if (direction == Arten::Direction::Down) {
		setPosition(sf::Vector2f(getPosition().x, getPosition().y + playerSpeedY));
		score_ -= 10;
		setState(Frogger::State::JumpDown);
	}
	setStateCountdownToZero();

	SoundSystem::Instance().playSound(SoundSystem::Sound::hop);
}

void Frogger::respawnFrogger()
{
	setState(Arten::State::IdleUp);
	setPosition(respawnPosition_);
	resetPositionFlags();
}


void Frogger::updateStates()
{
	const sf::Time JUMP = sf::milliseconds(100);
	const sf::Time DEATHTIMING = sf::milliseconds(1200);

	if (state_ == Arten::State::Death && stateCountdown_ > DEATHTIMING) {
		livesLeft_ -= 1;
		if (livesLeft_ > 0)
			respawnFrogger();
	}
	else if (state_ == Arten::State::JumpLeft && (stateCountdown_ > JUMP)) {
		setState(Arten::State::IdleLeft);
	}
	else if (state_ == Arten::State::JumpRight && (stateCountdown_ > JUMP)) {
		setState(Arten::State::IdleRight);
	}
	else if (state_ == Arten::State::JumpUp && (stateCountdown_ > JUMP)) {
		setState(Arten::State::IdleUp);
	}
	else if (state_ == Arten::State::JumpDown && (stateCountdown_ > JUMP)) {
		setState(Arten::State::IdleDown);
	}

	if (isStruckByCar_ || (isInRiver_ && !isOnSwimmingNPC_) || isWinningSpotTaken_) {
		setState(Arten::State::Death);
		if (isInRiver_ && !isOnSwimmingNPC_)
			SoundSystem::Instance().playSound(SoundSystem::Sound::plunk);
		else if (isStruckByCar_)
			SoundSystem::Instance().playSound(SoundSystem::Sound::squash);
	}
}

void Frogger::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	stateCountdown_ += dt;
	updateStates();

	auto rec = animations_.at(state_).update(dt);

	move(geschwindigkeit * dt.asSeconds());

	sprite_.setTextureRect(rec);
	centerOrigin(sprite_);
}

void Frogger::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

//Huaptmenu Funktionen
MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
	, options()
	, optionIndex(0)
{

	sf::Font& font = context.fonts->get(FontID::Main);

	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	options.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
	options.push_back(exitOption);

	updateOptionText();

}

void MenuState::draw()
{
	auto& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(backgroundSprite);

	for (const auto& text : options) {
		window.draw(text);
	}
}

bool MenuState::update(sf::Time dt)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
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
			optionIndex = options.size() - 1;

		updateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		if (optionIndex < options.size() - 1)
			optionIndex++;
		else
			optionIndex = 0;

		updateOptionText();
	}

	return true;
}

void MenuState::updateOptionText() {
	if (options.empty())
		return;

	for (auto& text : options)
		text.setFillColor(sf::Color::White);

	options[optionIndex].setFillColor(sf::Color::Blue);
}

//Pause Menu
PauseState::PauseState(StateStack& stack, Context context)
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
	centerOrigin(pauseText);
	pauseText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	hilfeText.setFont(font);
	hilfeText.setString("Escape to go to main Menu");
	hilfeText.setCharacterSize(20);
	centerOrigin(hilfeText);
	hilfeText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw()
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

