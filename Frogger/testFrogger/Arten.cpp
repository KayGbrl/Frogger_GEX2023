#include "Arten.h"
#include "Elemente.h"
#include "ElementErkennung.h"
#include "JsonFrameParser.h"
#include "DataTables.h"


#include <SFML/Graphics/RenderTarget.hpp>

namespace
{
	const std::map<Arten::Type, Karachtere> TABLE = artenData();
}

Arten::Arten(Type type, const TextureHolder_t& textures, const FontHolder_t& fonts)
	: Entity(100)
	, typen(type)
	, status(SpeilStatus::Still)
	, sprite_(textures.get(TABLE.at(type).texturen))
	, richtungen(Direction::Up)
{
	for (auto a : TABLE.at(type).animationen)
	{
		animationen[a.first] = a.second;
	}

	sprite_.setTextureRect(animationen[Arten::SpeilStatus::Still].gameCurrentFrame());
	centerOrigin(sprite_);

}

Arten::Arten(const TextureHolder_t& textures, const FontHolder_t& fonts)
	: Entity(100)
	, typen(Type::Frogger)
{}

unsigned int Arten::getCategory() const
{
	switch (typen)
	{
	case Type::Frogger:
		return Category::Frogger;
		break;
	case Type::Gelbesauto:
	case Type::Gruenesauto:
	case Type::Pinkesauto:
		return Category::Auto;
		break;
	case Type::Traktor:
	case Type::Lkw:
		return Category::Truck;
		break;
	case Type::Kleinerstamm:
	case Type::Grosserstamm:
		return Category::Stamm;
		break;
	case Type::Alligator:
		return Category::Alligator;
		break;
	case Type::Zweierkroete:
		return Category::Zweierkroete;
		break;
	case Type::Dreierkroete:
		return Category::Dreierkroete;
		break;
	case Type::Zweierkroete_Untertauchen:
		return Category::Zweierkroete_Untertauchen;
		break;
	case Type::Dreierkroete_Untertauchen:
		return Category::Dreierkroete_Untertauchen;
		break;
	case Type::Pinkerfrosh:
		return Category::Pinkerfrosh;
		break;
	case Type::Schlange:
		return Category::Schlange;
		break;
	case Type::Fliege:
		return Category::Fliege;
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

float Arten::speed() const
{
	return 0.f;
}

bool Arten::zumEntfernen() const
{
	return isMarkedForRemoval_; 
}

void Arten::setMarkedForRemoval(bool b)
{
	isMarkedForRemoval_ = b;
}

void Arten::Statussetzen(SpeilStatus state)
{
	status = state;
	animationen[status].restart();
}

Arten::SpeilStatus Arten::StatusGeben() const
{
	return status;
}

void Arten::RichtungSetzen(Arten::Direction d)
{
	richtungen = d;
}

Arten::Direction Arten::RichtungGEebn() const
{
	return richtungen;
}

void Arten::states()
{
	const sf::Time timeToJump = sf::milliseconds(100);
}

void Arten::aktuellesBild(sf::Time dt, CommandQueue& commands)
{
	states();

	auto rec = animationen.at(status).gameCurrentFrame();
	//if (!(type_ == Type::Turtle2 || type_ == Type::Turtle3))
		rec = animationen.at(status).update(dt);

	move(geschwindigkeit * dt.asSeconds());

	sprite_.setTextureRect(rec);
	centerOrigin(sprite_);
}

void Arten::aktuellezeichnen(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}
