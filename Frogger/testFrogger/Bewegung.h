#pragma once

#include "Category.h"
#include "Bewegung.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <map>
#include <cassert>
#include <functional>

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
	void				eingabe(CommandQueue& commands);

	void				aufgabeGeben(MissionStatus status);
	MissionStatus		aufgabeBekommen() const;

private:
	void				actionMachen();
	void				tastenSchlag();
	static bool			echtzeit(Action action);

	MissionStatus		missionsZiel;

private:
	std::map<sf::Keyboard::Key, Action>		tastenBelegung;
	std::map<Action, Kommando>				bewegungMachen;

};

