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


struct Karachtere
{
	TextureID							texturen;
	std::map<Arten::SpeilStatus, Animation>	animationen;
	std::vector<Arten::Direction>	    richtungen;
};

struct NPCSpawnData {
	sf::Vector2f						position;
	Arten::Direction					richtung;
	Arten::Type							type;
	float								speed;
	sf::Time							interval;
	sf::Time							elapsedTime;
	bool								spawn;
};

std::map<Arten::Type, Karachtere> initializeActorData();

std::vector<NPCSpawnData> initializeNPCSpawnData();

std::vector<sf::FloatRect> getWinningSpotPositions();

