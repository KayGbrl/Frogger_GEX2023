#pragma once

#include <SFML/Window/Event.hpp>
#include "Bewegung.h"
#include <map>

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

