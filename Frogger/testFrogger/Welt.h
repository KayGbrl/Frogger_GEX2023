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
#include "SFML/Graphics/Rect.hpp"

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

	sf::FloatRect			getViewBounds() const;
	sf::FloatRect			gameBounds() const;

	void					NPCDaten(sf::Time dt);

	void					addEnemies();
	void					collisions();
	void					entitiesOutsideView();

	bool					kategorien(SceneNode::Pair& colliders, Category::Typen type1, Category::Typen type2);

	void					lebensAnzeige(int amount);
	void					lebensAnzeigeAufbauen(int frogLives);

	void					updateText();

	int						ziellocationI(sf::FloatRect pos);
	bool					zielGefulltKomplett();

	void playerPosition();

private:
	enum Layer
	{
		Hintergrund,
		Leben,
		Fluss,
		SpielFeld,
		LagenDerWelt
	};


private:
	sf::RenderTarget& target;
	sf::RenderTexture					texturenSzene_;
	sf::View							weltAnsicht_;
	TextureHolder_t						texturen_;
	const FontHolder_t& fonts;
	TextNode* score;

	SceneNode							szenen_;
	std::array<SceneNode*, LagenDerWelt>	szenenSchichten_;
	CommandQueue						kommando_;

	sf::FloatRect						worldBounds;
	sf::Vector2f						spawnPosition;
	float								scrollSpeed;
	Frogger* playerFrogger;

	std::vector<NPCSpawnData>			npcErscheinung_;
	std::vector<bool>					zielistGefullt_;
	std::vector<std::unique_ptr<SpriteNode>>			livesToShow;

	float frogSpawnTimer = 0.f;
	float alligHeadTimer = 0.f;

};

//Positionen und wand der welt elemente
class InteractablePlaceHolder : public SceneNode
{
public:
	InteractablePlaceHolder(Category::Typen category);
	InteractablePlaceHolder(Category::Typen category, sf::FloatRect pos);

	sf::FloatRect		getPosition() const;
	void				setPosition(sf::FloatRect pos);

	sf::FloatRect		getBoundingRect() const;

private:
	sf::FloatRect			position;
};

