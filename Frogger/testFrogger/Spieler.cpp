//#include "Arten.h"
//#include "Spieler.h"
//#include <algorithm>
//#include "Ausloser.h"
//#include "Frogger.h"
//#include "SoundSystem.h"
//
//Player::Player()
//	: currentMissionStatus(MissionStatus::Running)
//{
//	initializeKeyBindings();
//	initializeActions();
//
//	for (auto& pair : actionBindings) {
//		pair.second.category = Category::Frogger;
//	}
//}
//
//void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
//{
//	if (event.type == sf::Event::KeyPressed)
//	{
//		auto found = keyBindings.find(event.key.code);
//		if (found != keyBindings.end() && !isRealtimeAction(found->second))
//			commands.push(actionBindings[found->second]);
//	}
//}
//
//void Player::handleRealTimeInput(CommandQueue& commands)
//{
//	for (auto pair : keyBindings) {
//
//		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
//			commands.push(actionBindings[pair.second]);
//	}
//}
//
//void Player::setMissionStatus(MissionStatus status)
//{
//	currentMissionStatus = status;
//}
//
//Player::MissionStatus Player::getMissionStatus() const
//{
//	return currentMissionStatus;
//}
//
//void Player::initializeKeyBindings() {
//	keyBindings[sf::Keyboard::Left] = Action::MoveLeft;
//	keyBindings[sf::Keyboard::Right] = Action::MoveRight;
//	keyBindings[sf::Keyboard::Up] = Action::MoveUp;
//	keyBindings[sf::Keyboard::Down] = Action::MoveDown;
//
//	keyBindings[sf::Keyboard::A] = Action::MoveLeft;
//	keyBindings[sf::Keyboard::D] = Action::MoveRight;
//	keyBindings[sf::Keyboard::W] = Action::MoveUp;
//	keyBindings[sf::Keyboard::S] = Action::MoveDown;
//}
//
//
//void Player::initializeActions()
//{
//	actionBindings[Action::MoveLeft].action = derivedAction<Frogger>(
//		[](Frogger& a, sf::Time dt) {
//			a.hop(Arten::Direction::Left);
//		});
//
//	actionBindings[Action::MoveRight].action = derivedAction<Frogger>(
//		[](Frogger& a, sf::Time dt) {
//			a.hop(Arten::Direction::Right);
//		});
//
//	actionBindings[Action::MoveUp].action = derivedAction<Frogger>(
//		[](Frogger& a, sf::Time dt) {
//			a.hop(Arten::Direction::Up);
//		});
//
//	actionBindings[Action::MoveDown].action = derivedAction<Frogger>(
//		[](Frogger& a, sf::Time dt) {
//			a.hop(Arten::Direction::Down);
//		});
//}
//
//bool Player::isRealtimeAction(Action action)
//{
//	switch (action)
//	{
//	case Action::MoveLeft: 
//	case Action::MoveRight:
//	case Action::MoveDown:
//	case Action::MoveUp:
//		return false;
//	default:
//		return false;
//	}
//}
