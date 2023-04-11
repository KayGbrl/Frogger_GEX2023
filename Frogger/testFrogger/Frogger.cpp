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
	, bilder_(textures.get(TABLE.at(Arten::Type::Frogger).texturen))
	, richtung_(Direction::Up)
	, richtungI_(0)
	, Status_(sf::Time::Zero)
	, respawnPosition_(240.f, 580.f)
	, Leben_(7)
	, zumEntfernen_(false)
	, spielerImZielSpot_(false)
{
	for (auto a : TABLE.at(Arten::Type::Frogger).animationen)
	{
		animationen_[a.first] = a.second;
	}

	bilder_.setTextureRect(animationen_[Arten::SpeilStatus::Stehenhoch].gameCurrentFrame());
	zentrierterPunkt(bilder_);

	GeschwindigkeitSetzen(0.f, 0.f);
}

unsigned int Frogger::kategoryBekommen() const
{
	return Category::Frogger;
}

sf::FloatRect Frogger::ruckstossBekommenRechteck() const
{
	auto box = weltTransformiert().transformRect(bilder_.getGlobalBounds());
	box.width -= 10; 
	box.left += 5;
	box.top += 5;
	box.height -= 10;
	return box;
}

float Frogger::GeschwindigkeitMax() const
{
	return 0.f;
}

bool Frogger::zumEntfernen() const
{
	return zumEntfernen_;
}

void Frogger::alleZielegefullt()
{
	spielerImZielSpot_ = true;
}

bool Frogger::SPielerZielErreicht() const
{
	return spielerImZielSpot_;
}

void Frogger::Zieleingenommen()
{
	zielGefuhllt_ = true;
}

void Frogger::statusSetzen(SpeilStatus state)
{
	if (status_ != state) {
		status_ = state;
		animationen_[status_].restart();
	}
}

Frogger::SpeilStatus Frogger::statusBekommen() const
{
	return status_;
}

bool Frogger::vomAutoGetrofen() const
{
	return vomAutogetroffen;
}

void Frogger::imWasser(bool b)
{
	vomAutogetroffen = b;
}

bool Frogger::insWasserGefallen() const
{
	return ImWasser;
}

void Frogger::imWasserGestzt(bool b)
{
	ImWasser = b;
}

bool Frogger::aufSchwimmendeGegenr() const
{
	return aufSchwimmendenGeggner_;
}

void Frogger::spielerAufSchwimmendeGegner(bool b)
{
	aufSchwimmendenGeggner_ = b;
}

void Frogger::zurusetzenFlagge()
{
	vomAutogetroffen = false;
	ImWasser = false;
	aufSchwimmendenGeggner_ = false;
	zielGefuhllt_ = false;
}

void Frogger::limitAufNull()
{
	Status_ = sf::Time::Zero;
}

sf::Time Frogger::getStateCountdown()
{
	return Status_;
}

int Frogger::scorebekommen()
{
	return punktezahl_;
}

void Frogger::punkteAufrechnen(int score)
{
	punktezahl_ += score;
}

int Frogger::ueberbleibendeLeben()
{
	return Leben_;
}

void Frogger::lebenAbziehen()
{
	Leben_ -= 1;
}

void Frogger::hop(Arten::Direction direction)
{
	const float playerSpeedY = 40.f;
	const float playerSpeedX = 50.f;

	if (status_ == Arten::SpeilStatus::Tod)
		return;

	if (direction == Arten::Direction::Links) {
		setPosition(sf::Vector2f(getPosition().x - playerSpeedX, getPosition().y));
		statusSetzen(Frogger::SpeilStatus::Links);
	}
	else if (direction == Arten::Direction::Rechts) {
		setPosition(sf::Vector2f(getPosition().x + playerSpeedX, getPosition().y));
		statusSetzen(Frogger::SpeilStatus::Rechts);
	}
	else if (direction == Arten::Direction::Oben) {
		setPosition(sf::Vector2f(getPosition().x, getPosition().y - playerSpeedY));
		punktezahl_ += 10;
		statusSetzen(Frogger::SpeilStatus::Hoch);
	}
	else if (direction == Arten::Direction::Unten) {
		setPosition(sf::Vector2f(getPosition().x, getPosition().y + playerSpeedY));
		punktezahl_ -= 5;
		statusSetzen(Frogger::SpeilStatus::Runter);
	}
	limitAufNull();

	SoundSystem::Instance().playSound(SoundSystem::Sound::hop);
}

void Frogger::respawnFrogger()
{
	statusSetzen(Arten::SpeilStatus::Stehenhoch);
	setPosition(respawnPosition_);
	zurusetzenFlagge();
}


void Frogger::updateStates()
{
	const sf::Time SPRUNG = sf::milliseconds(100);
	const sf::Time TODESZEITPUNKT = sf::milliseconds(1200);

	if (status_ == Arten::SpeilStatus::Tod && Status_ > TODESZEITPUNKT) {
		Leben_ -= 1;
		if (Leben_ > 0)
			respawnFrogger();
	}
	else if (status_ == Arten::SpeilStatus::Links && (Status_ > SPRUNG)) {
		statusSetzen(Arten::SpeilStatus::Stehenlinks);
	}
	else if (status_ == Arten::SpeilStatus::Rechts && (Status_ > SPRUNG)) {
		statusSetzen(Arten::SpeilStatus::Stehenrechts);
	}
	else if (status_ == Arten::SpeilStatus::Hoch && (Status_ > SPRUNG)) {
		statusSetzen(Arten::SpeilStatus::Stehenhoch);
	}
	else if (status_ == Arten::SpeilStatus::Runter && (Status_ > SPRUNG)) {
		statusSetzen(Arten::SpeilStatus::Stehenrunter);
	}

	if (vomAutogetroffen || (ImWasser && !aufSchwimmendenGeggner_) || zielGefuhllt_) {
		statusSetzen(Arten::SpeilStatus::Tod);
		if (ImWasser && !aufSchwimmendenGeggner_)
			SoundSystem::Instance().playSound(SoundSystem::Sound::plunk);
		else if (vomAutogetroffen)
			SoundSystem::Instance().playSound(SoundSystem::Sound::squash);
	}
}

void Frogger::aktuellesBild(sf::Time dt, CommandQueue& commands)
{
	Status_ += dt;
	updateStates();

	auto rec = animationen_.at(status_).update(dt);

	move(geschwindigkeit * dt.asSeconds());

	bilder_.setTextureRect(rec);
	zentrierterPunkt(bilder_);
}

void Frogger::aktuellezeichnen(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bilder_, states);
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
	auto& window = *spielKontext().window;

	window.setView(window.getDefaultView());
	window.draw(hintergrund);

	for (const auto& text : optionen) {
		window.draw(text);
	}
}

bool Menu::aktualisieren(sf::Time dt)
{
	return true;
}

bool Menu::ereiknissHandeln(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{
		if (optionIndex == Play) {
			anordnungplepen();
			anordnungDrucken(StateID::Game);
		}
		else if (optionIndex == Exit)
		{
			anordnungplepen();
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
	sf::RenderWindow& window = *spielKontext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;

	backgroundShape.setFillColor(sf::Color(0, 0, 0, 70));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(pauseText);
	window.draw(hilfeText);
}

bool Pause::aktualisieren(sf::Time dt)
{
	return false;
}

bool Pause::ereiknissHandeln(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;
	if (event.key.code == sf::Keyboard::P)
	{
		anordnungplepen();
	}
	if (event.key.code == sf::Keyboard::Escape)
	{
		anordnungLeeren();
		anordnungDrucken(StateID::Menu);
	}
	return false;
}

