#pragma once

#include "ElementErkennung.h"
#include "Arten.h"
#include "Animation.h"
#include "Frogger.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

#include <map>
#include <vector>
#include <functional>


struct ActorData
{
	TextureID							texture;
	std::map<Arten::State, Animation>	animations;
	std::vector<Arten::Direction>	    directions;
};

struct NPCSpawnData {
	sf::Vector2f						position;
	Arten::Direction					direction;
	Arten::Type							type;
	float								speed;
	sf::Time							interval;
	sf::Time							elapsedTime;
	bool								spawn;
};

std::map<Arten::Type, ActorData> initializeActorData();

std::vector<NPCSpawnData> initializeNPCSpawnData();

std::vector<sf::FloatRect> getWinningSpotPositions();

