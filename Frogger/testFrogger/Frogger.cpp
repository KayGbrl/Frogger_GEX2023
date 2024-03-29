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
	, status_(SpeilStatus::Stehenhoch)
	, sprite_(textures.get(TABLE.at(Arten::Type::Frogger).texturen))
	, richtungen_(Direction::Up)
	, richtungIndex_(0)
	, stateCountdown_(sf::Time::Zero)
	, respawnPosition_(240.f, 580.f)
	, lebenUbrig_(7)
	, zumEnfernenMarkiet_(false)
	, hatSpielerspotgefullt_(false)
{
	for (auto a : TABLE.at(Arten::Type::Frogger).animationen)
	{
		animationen_[a.first] = a.second;
	}

	sprite_.setTextureRect(animationen_[Arten::SpeilStatus::Stehenhoch].gameCurrentFrame());
	centerOrigin(sprite_);

	GeschwindigkeitSetzen(0.f, 0.f);
}

unsigned int Frogger::getCategory() const
{
	return Category::Frogger;
}

sf::FloatRect Frogger::getBoundingRect() const
{
	auto box = weltAndern().transformRect(sprite_.getGlobalBounds());
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

void Frogger::hatFroggerZielGefulltsetzen()
{
	hatSpielerspotgefullt_ = true;
}

bool Frogger::froggerhatZielErreicht() const
{
	return hatSpielerspotgefullt_;
}

void Frogger::istImZiel()
{
	zielGebietGefullt_ = true;
}

void Frogger::setState(SpeilStatus state)
{
	if (status_ != state) {
		status_ = state;
		animationen_[status_].restart();
	}
}

Frogger::SpeilStatus Frogger::getState() const
{
	return status_;
}

bool Frogger::vomAutoGetriffen() const
{
	return vomAutoGetroffen_;
}

void Frogger::vomAutiGetroffenFestsetzen(bool b)
{
	vomAutoGetroffen_ = b;
}

bool Frogger::imFluss() const
{
	return imFluss_;
}

void Frogger::imFlussFestgesetzt(bool b)
{
	imFluss_ = b;
}

bool Frogger::aufSchwimmendenGegener() const
{
	return aufSchwimmendenGegner_;
}

void Frogger::spieleraufSchwimmendenGegener(bool b)
{
	aufSchwimmendenGegner_ = b;
}

void Frogger::zuruscksetzenPosition()
{
	vomAutoGetroffen_ = false;
	imFluss_ = false;
	aufSchwimmendenGegner_ = false;
	zielGebietGefullt_ = false;
}

void Frogger::zeitStatusSetzen()
{
	stateCountdown_ = sf::Time::Zero;
}

sf::Time Frogger::zeitStatusbekommen()
{
	return stateCountdown_;
}

int Frogger::punktezahlBekommen()
{
	return punkteZahl_;
}

void Frogger::punktezahldDraufrechnen(int score)
{
	punkteZahl_ += score;
}

int Frogger::lebenUbrigBekommen()
{
	return lebenUbrig_;
}

void Frogger::lebenReduzieren()
{
	lebenUbrig_ -= 1;
}

void Frogger::hop(Arten::Direction direction)
{
	const float playerSpeedY = 40.f;
	const float playerSpeedX = 50.f;

	if (status_ == Arten::SpeilStatus::Tod)
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
		punkteZahl_ += 10;
		setState(Frogger::SpeilStatus::Hoch);
	}
	else if (direction == Arten::Direction::Unten) {
		setPosition(sf::Vector2f(getPosition().x, getPosition().y + playerSpeedY));
		punkteZahl_ -= 10;
		setState(Frogger::SpeilStatus::Runter);
	}
	zeitStatusSetzen();

	SoundSystem::Instance().playSound(SoundSystem::Sound::hop);
}

void Frogger::respawnFrogger()
{
	setState(Arten::SpeilStatus::Stehenhoch);
	setPosition(respawnPosition_);
	zuruscksetzenPosition();
}


void Frogger::updateStates()
{
	const sf::Time SPRUNG = sf::milliseconds(100);
	const sf::Time TODESZEITPUNKT = sf::milliseconds(1200);

	if (status_ == Arten::SpeilStatus::Tod && stateCountdown_ > TODESZEITPUNKT) {
		lebenUbrig_ -= 1;
		if (lebenUbrig_ > 0)
			respawnFrogger();
	}
	else if (status_ == Arten::SpeilStatus::Links && (stateCountdown_ > SPRUNG)) {
		setState(Arten::SpeilStatus::Stehenlinks);
	}
	else if (status_ == Arten::SpeilStatus::Rechts && (stateCountdown_ > SPRUNG)) {
		setState(Arten::SpeilStatus::Stehenrechts);
	}
	else if (status_ == Arten::SpeilStatus::Hoch && (stateCountdown_ > SPRUNG)) {
		setState(Arten::SpeilStatus::Stehenhoch);
	}
	else if (status_ == Arten::SpeilStatus::Runter && (stateCountdown_ > SPRUNG)) {
		setState(Arten::SpeilStatus::Stehenrunter);
	}

	if (vomAutoGetroffen_ || (imFluss_ && !aufSchwimmendenGegner_) || zielGebietGefullt_) {
		setState(Arten::SpeilStatus::Tod);
		if (imFluss_ && !aufSchwimmendenGegner_)
			SoundSystem::Instance().playSound(SoundSystem::Sound::plunk);
		else if (vomAutoGetroffen_)
			SoundSystem::Instance().playSound(SoundSystem::Sound::squash);
	}
}

void Frogger::aktuellesBild(sf::Time dt, CommandQueue& commands)
{
	stateCountdown_ += dt;
	updateStates();

	auto rec = animationen_.at(status_).update(dt);

	move(geschwindigkeit * dt.asSeconds());

	sprite_.setTextureRect(rec);
	centerOrigin(sprite_);
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
	centerOrigin(playOption);
	playOption.setPosition(context.window->getView().getSize() / 2.f);
	optionen.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
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
			erwarteStapelkaput();
			erwarteStapelDrucken(StateID::Spiel);
		}
		else if (optionIndex == Exit)
		{
			erwarteStapelkaput();
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
	centerOrigin(pauseText);
	pauseText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	hilfeText.setFont(font);
	hilfeText.setString("Escape to go to main Menu");
	hilfeText.setCharacterSize(20);
	centerOrigin(hilfeText);
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
		erwarteStapelkaput();
	}
	if (event.key.code == sf::Keyboard::Escape)
	{
		erwarteStatusReinigung();
		erwarteStapelDrucken(StateID::Menu);
	}
	return false;
}

