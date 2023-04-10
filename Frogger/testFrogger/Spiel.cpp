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

void State::requestStackPush(StateID stateID)
{
	stack->stapelAbgeben(stateID);
}

void State::requestStackPop()
{
	stack->stapelRausdrucken();
}

void State::requestStateClear()
{
	stack->statusLeeren();
}

State::Context State::getContext()
{
	return context;
}


State::~State() {}
