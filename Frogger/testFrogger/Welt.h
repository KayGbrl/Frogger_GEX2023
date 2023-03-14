
#pragma once

#include "Elemente.h"
#include "ElementErkennung.h"
#include "SzenenElemente.h"
#include "SpriteElemente.h"
#include "Ausloser.h"
#include "Bewegung.h"
#include "Arten.h"
#include "DataTables.h"
#include "Text.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <array>

namespace sf {
	class RenderTarget;
}

class World : private sf::NonCopyable {

public:
	explicit				World(sf::RenderTarget& window,
		const FontHolder_t& fonts);
	void					update(sf::Time dt);
	void					draw();

	CommandQueue& getCommands();

	bool					playerAlive() const;
	bool					reachedEnd() const;

private:
	void					loadTextures();
	void					buildScene();

	void					addEnemies();
	void					collisions();
	bool					categories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
	void					entitiesOutsideView();

	void					liveIndicator(int amount);
	void					buildLivesIndicator(int frogLives);

	void					updateText();

	void					updateNPCSpawnTable(sf::Time dt);

	sf::FloatRect			getViewBounds() const;
	sf::FloatRect			gameBounds() const;

	int						winnningSpotIndex(sf::FloatRect pos);
	bool					winningSpotsFull();

	void playerPosition();

private:
	enum Layer
	{
		Background,
		Lives,
		River,
		PlayingLayer,
		LayerCount
	};


private:
	sf::RenderTarget& target;
	sf::RenderTexture					sceneTexture;
	sf::View							worldView;
	TextureHolder_t						textures;
	const FontHolder_t& fonts;
	TextNode* score;

	SceneNode							sceneGraph;
	std::array<SceneNode*, LayerCount>	sceneLayers;
	CommandQueue						commandQueue;

	sf::FloatRect						worldBounds;
	sf::Vector2f						spawnPosition;
	float								scrollSpeed;
	Frogger* playerFrogger;

	std::vector<NPCSpawnData>			npcSpawnTable;
	std::vector<bool>					winningSpotsFilled;
	std::vector<std::unique_ptr<SpriteNode>>			livesToShow;

	float frogSpawnTimer = 0.f;

};
