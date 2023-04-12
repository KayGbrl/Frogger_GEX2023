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
	void				registerState(StateID stateID);

	void				update(sf::Time dt);
	void				zeichen();
	void				handleEvent(const sf::Event& event);

	void				statusDrucken(StateID stateID);
	void				statusWeg();
	void				statusleeren();

	bool				istLeer() const;


private:
	State::Ptr			statusKreieren(StateID stateID);
	void				austehendeAnderungenAnwenden();

private:
	struct PendingChange
	{
		explicit			PendingChange(Action action, StateID stateID = StateID::None);
		Action				action;
		StateID				stateID;
	};

private:
	std::vector<State::Ptr>								stapel_;
	std::vector<PendingChange>							wartenListe_;

	State::Context										context;
	std::map<StateID, std::function<State::Ptr()>>		factories;
};


template <typename T>
void StateStack::registerState(StateID stateID)
{
	factories[stateID] = [this]()
	{
		return State::Ptr(new T(*this, context));
	};
}