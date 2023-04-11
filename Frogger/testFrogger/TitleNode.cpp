#include "Spiel.h"
#include "Elemente.h"
#include "SpriteElemente.h"

#include <SFML/Graphics/RenderWindow.hpp>

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	, text()
	, textZeigen(true)
	, textEffekte(sf::Time::Zero)
{
	hintergrundBild.setTexture(context.textures->get(TextureID::TitleScreen));

	text.setFont(context.fonts->get(FontID::Main));
	text.setString("Press Enter");

	zentrierterPunkt(text);
	text.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw()
{
	auto& window = *spielKontext().window;
	window.draw(hintergrundBild);

	if (textZeigen)
		window.draw(text);
}

bool TitleState::aktualisieren(sf::Time dt)
{
	textEffekte += dt;

	if (textEffekte >= sf::seconds(0.5f)) {
		textZeigen = !textZeigen;
		textEffekte = sf::Time::Zero;
	}

	return true;
}

bool TitleState::ereiknissHandeln(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		anordnungplepen();
		anordnungDrucken(StateID::Menu);
	}
	return true;
}
