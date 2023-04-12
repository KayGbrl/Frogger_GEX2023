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
	: stack(&stack)
	, context(context)
{}

void State::erwarteStapelDrucken(StateID stateID)
{
	stack->statusDrucken(stateID);
}

void State::erwarteStapelkaput()
{
	stack->statusWeg();
}

void State::erwarteStatusReinigung()
{
	stack->statusleeren();
}

State::Context State::getContext()
{
	return context;
}


State::~State() {}
