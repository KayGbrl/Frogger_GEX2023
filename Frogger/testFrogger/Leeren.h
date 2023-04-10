#pragma once

#include "Spiel.h"
#include "StatenCheck.h"
#include "ElementErkennung.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>

namespace sf
{
	class Event;
	class RenderWindow;
}

class StateStack : private sf::NonCopyable
{

public:
	enum class Action
	{
		Push,
		Pop,
		Clear,
	};

public:
	explicit			StateStack(State::Context context);

	template <typename T>
	void				statusRegistrieren(StateID stateID);

	void				aktualisiren(sf::Time dt);
	void				zeichnen();
	void				handleEvent(const sf::Event& event);

	void				stapelAbgeben(StateID stateID);
	void				stapelRausdrucken();
	void				statusLeeren();

	bool				istLeer() const;


private:
	State::Ptr			stapelErstellen(StateID stateID);
	void				veraenderungenAktualisieren();

private:
	struct PendingChange
	{
		explicit			PendingChange(Action action, StateID stateID = StateID::None);
		Action				action;
		StateID				stateID;
	};

private:
	std::vector<State::Ptr>								stapeln;
	std::vector<PendingChange>							ausstehend;

	State::Context										kontext;
	std::map<StateID, std::function<State::Ptr()>>		factoren;
};


template <typename T>
void StateStack::statusRegistrieren(StateID stateID)
{
	factoren[stateID] = [this]()
	{
		return State::Ptr(new T(*this, kontext));
	};
}