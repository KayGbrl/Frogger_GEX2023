#pragma once

#include "Elemente.h"
#include "ElementErkennung.h"
#include "Leeren.h"
#include "Bewegung.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#pragma once
class Application
{
public:
	Application();
	void					starten();

private:
	void					eingabe();
	void					update(sf::Time dt);
	void					rendern();

	void					Statusregistrieren();

private:
	static const sf::Time	zeitImFrame;

	sf::RenderWindow		fenster;
	TextureHolder_t			texturen;
	FontHolder_t			fonts;
	Player					spieler;

	StateStack				statusStaffelung;

	sf::Text				textStatus;
	sf::Time				zeitDerStaten;
	std::size_t				statusDerFrames;


};

