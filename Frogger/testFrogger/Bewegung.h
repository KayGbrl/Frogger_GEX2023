#pragma once

#include <SFML/System/Time.hpp>
#include <functional>
#include <cassert>
#include "Category.h"

#include <SFML/Window/Event.hpp>
#include "Bewegung.h"
#include <map>


class SceneNode;

struct Kommando
{
	Kommando();
	std::function <void(SceneNode&, sf::Time)> action;
	unsigned int category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	return [=](SceneNode& node, sf::Time dt)
	{
		fn(static_cast<GameObject&>(node), dt);
	};
}

class CommandQueue;

class Player
{
public:
	enum class Action {
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,

		ActionCound,
	};

	enum class MissionStatus {
		Running,
		Success,
		Failure
	};

public:
	Player();

	void				handleEvent(const sf::Event& event, CommandQueue& commands);
	void				handleRealTimeInput(CommandQueue& commands);

	void				setMissionStatus(MissionStatus status);
	MissionStatus		getMissionStatus() const;

private:
	void				initializeActions();
	void				initializeKeyBindings();
	static bool			isRealtimeAction(Action action);

	MissionStatus		currentMissionStatus;

private:
	std::map<sf::Keyboard::Key, Action>		keyBindings;
	std::map<Action, Kommando>				actionBindings;

};

