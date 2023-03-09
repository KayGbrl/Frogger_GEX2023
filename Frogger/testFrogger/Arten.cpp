
#include "Arten.h"
#include "Elemente.h"
#include "ElementErkennung.h"
#include "JsonFrameParser.h"
#include "Werkzeug.h"
#include "DataTables.h"

#include <SFML/Graphics/RenderTarget.hpp>

namespace
{
	const std::map<Arten::Type, ActorData> TABLE = initializeActorData();
}

Arten::Arten(Type type, const TextureHolder_t& textures, const FontHolder_t& fonts)
	: Entity(100)
	, type_(type)
	, state_(State::Idle)
	, sprite_(textures.get(TABLE.at(type).texture))
	, direction_(Direction::Up)
{
	for (auto a : TABLE.at(type).animations)
	{
		animations_[a.first] = a.second;
	}

	sprite_.setTextureRect(animations_[Arten::State::Idle].getCurrentFrame());
	centerOrigin(sprite_);

}

Arten::Arten(const TextureHolder_t& textures, const FontHolder_t& fonts)
	: Entity(100)
	, type_(Type::Frogger)
{}

unsigned int Arten::getCategory() const
{
	switch (type_)
	{
	case Type::Frogger:
		return Category::Frogger;
		break;
	case Type::Car1:
	case Type::Car2:
	case Type::Car3:
		return Category::Car;
		break;
	case Type::Truck1:
	case Type::Truck2:
		return Category::Truck;
		break;
	case Type::Log1:
	case Type::Log2:
		return Category::Log;
		break;
	case Type::Alligator:
		return Category::Alligator;
		break;
	case Type::Turtle2:
		return Category::Turtle2;
		break;
	case Type::Turtle3:
		return Category::Turtle3;
		break;
	case Type::Turtle2_floating:
		return Category::Turtle2_floating;
		break;
	case Type::Turtle3_floating:
		return Category::Turtle3_floating;
		break;
	case Type::PinkFrog:
		return Category::PinkFrog;
		break;
	default:
		return Category::None;
	}

	return Category::NPC;
}

sf::FloatRect Arten::getBoundingRect() const
{
	auto box = getWorldTransform().transformRect(sprite_.getGlobalBounds());
	box.width -= 10; 
	box.left += 5;
	box.top += 5;
	box.height -= 10;
	return box;
}

float Arten::getMaxSpeed() const
{
	return 0.f;
}

bool Arten::isMarkedForRemoval() const
{
	return isMarkedForRemoval_; 
}

void Arten::setMarkedForRemoval(bool b)
{
	isMarkedForRemoval_ = b;
}

void Arten::setState(State state)
{
	state_ = state;
	animations_[state_].restart();
}

Arten::State Arten::getState() const
{
	return state_;
}

void Arten::setDirection(Arten::Direction d)
{
	direction_ = d;
}

Arten::Direction Arten::getDirection() const
{
	return direction_;
}

void Arten::updateStates()
{
	const sf::Time timeToJump = sf::milliseconds(100);
}

void Arten::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	updateStates();

	auto rec = animations_.at(state_).getCurrentFrame();
	//if (!(type_ == Type::Turtle2 || type_ == Type::Turtle3))
		rec = animations_.at(state_).update(dt);

	move(velocity * dt.asSeconds());

	sprite_.setTextureRect(rec);
	centerOrigin(sprite_);
}

void Arten::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}
