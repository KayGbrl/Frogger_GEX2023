#include "Leeren.h"

#include <cassert>

StateStack::StateStack(State::Context context)
	: stapeln()
	, ausstehend()
	, kontext(context)
	, factoren()
{}

void StateStack::aktualisiren(sf::Time dt)
{
	for (auto itr = stapeln.rbegin(); itr != stapeln.rend(); itr++) {
		if (!(*itr)->aktualisieren(dt))
			break;
	}
	veraenderungenAktualisieren();
}

void StateStack::zeichnen()
{
	for (auto& state : stapeln) {
		state->draw();
	}
}

void StateStack::handleEvent(const sf::Event& event)
{
	for (auto itr = stapeln.rbegin(); itr != stapeln.rend(); ++itr) {
		if (!(*itr)->ereiknissHandeln(event))
			break;
	}
	veraenderungenAktualisieren();
}

void StateStack::stapelAbgeben(StateID stateID)
{
	ausstehend.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::stapelRausdrucken()
{
	ausstehend.push_back(PendingChange(Action::Pop));
}

void StateStack::statusLeeren()
{
	ausstehend.push_back(PendingChange(Action::Clear));
}

bool StateStack::istLeer() const
{
	return stapeln.empty();
}

State::Ptr StateStack::stapelErstellen(StateID stateID)
{
	auto found = factoren.find(stateID);
	assert(found != factoren.end());

	return found->second();
}

void StateStack::veraenderungenAktualisieren()
{
	for (PendingChange change : ausstehend)
	{
		switch (change.action)
		{
		case Action::Push:
			stapeln.push_back(stapelErstellen(change.stateID));
			break;
		case Action::Pop:
			stapeln.pop_back();
			break;
		case Action::Clear:
			stapeln.clear();
			break;
		}
	}
	ausstehend.clear();
}

StateStack::PendingChange::PendingChange(Action action, StateID stateID)
	: action(action)
	, stateID(stateID)
{}
