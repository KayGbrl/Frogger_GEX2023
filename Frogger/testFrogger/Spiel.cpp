#include "Spiel.h"
#include "Leeren.h"


State::Context::Context(
	sf::RenderWindow& window,
	TextureHolder_t& textures,
	FontHolder_t& fonts,
	Player& player)
	: window(&window)
	, textures(&textures)
	, fonts(&fonts)
	, player(&player)
{}

State::State(StateStack& stack, Context context)
	: stapel(&stack)
	, Kontext(context)
{}

void State::anordnungDrucken(StateID stateID)
{
	stapel->stapelAbgeben(stateID);
}

void State::anordnungplepen()
{
	stapel->stapelRausdrucken();
}

void State::anordnungLeeren()
{
	stapel->statusLeeren();
}

State::Context State::spielKontext()
{
	return Kontext;
}


State::~State() {}
