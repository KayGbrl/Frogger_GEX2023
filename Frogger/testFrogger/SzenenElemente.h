#include "Bewegung.h"
#include "Category.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <memory>
#include <set>

class CommandQueue;

#pragma once
class SceneNode :
	public sf::Transformable,
	public sf::Drawable,
	private sf::NonCopyable
{
public:
	using Ptr = std::unique_ptr<SceneNode>;
	using Pair = std::pair<SceneNode*, SceneNode*>;

public:
	SceneNode(Category::Typen c = Category::Typen::None);

	void				attachChild(Ptr child);
	Ptr					detachChild(const SceneNode& node);

	void				update(sf::Time dt, CommandQueue& commands);
	void				checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
	void				checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
	void				kaputteEntfernen();


	sf::Vector2f		getWorldPoition()	const;
	sf::Transform		getWorldTransform() const;
	virtual sf::FloatRect ruckstossBekommenRechteck() const;
	virtual bool		  zumEntfernen() const;
	virtual bool		  zerstoert() const;
	virtual unsigned int  kategoryBekommen() const;
	void				onCommand(const Kommando& command, sf::Time dt);

private:
	virtual void		aktuellesBild(sf::Time dt, CommandQueue& commands);
	virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void		aktuellezeichnen(sf::RenderTarget& target, sf::RenderStates states) const;
	void				kindZeichnen(sf::RenderTarget& target, sf::RenderStates states) const;

	void				kinderneuern(sf::Time dt, CommandQueue& commands);

	void				drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;



private:
	std::vector<Ptr>	kinder;
	SceneNode* parent;
	Category::Typen		Kategory;
};

float calculateDistance(const SceneNode& lhs, const SceneNode& rhs);
bool isColliding(const SceneNode& lhs, const SceneNode& rhs);

