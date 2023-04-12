#include "Leeren.h"

#include <cassert>

StateStack::StateStack(State::Context context)
	: stapel_()
	, wartenListe_()
	, context(context)
	, factories()
{}

void StateStack::update(sf::Time dt)
{
	for (auto itr = stapel_.rbegin(); itr != stapel_.rend(); itr++) {
		if (!(*itr)->update(dt))
			break;
	}
	austehendeAnderungenAnwenden();
}

void StateStack::zeichen()
{
	for (auto& state : stapel_) {
		state->draw();
	}
}

void StateStack::handleEvent(const sf::Event& event)
{
	for (auto itr = stapel_.rbegin(); itr != stapel_.rend(); ++itr) {
		if (!(*itr)->handleEvent(event))
			break;
	}
	austehendeAnderungenAnwenden();
}

void StateStack::statusDrucken(StateID stateID)
{
	wartenListe_.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::statusWeg()
{
	wartenListe_.push_back(PendingChange(Action::Pop));
}

void StateStack::statusleeren()
{
	wartenListe_.push_back(PendingChange(Action::Clear));
}

bool StateStack::istLeer() const
{
	return stapel_.empty();
}

State::Ptr StateStack::statusKreieren(StateID stateID)
{
	auto found = factories.find(stateID);
	assert(found != factories.end());

	return found->second();
}

void StateStack::austehendeAnderungenAnwenden()
{
	for (PendingChange change : wartenListe_)
	{
		switch (change.action)
		{
		case Action::Push:
			stapel_.push_back(statusKreieren(change.stateID));
			break;
		case Action::Pop:
			stapel_.pop_back();
			break;
		case Action::Clear:
			stapel_.clear();
			break;
		}
	}
	wartenListe_.clear();
}

StateStack::PendingChange::PendingChange(Action action, StateID stateID)
	: action(action)
	, stateID(stateID)
{}
