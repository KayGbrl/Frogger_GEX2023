#include "SzenenElemente.h"
#include "Category.h"
#include "bewegung.h"
#include "Ausloser.h"
#include "Elemente.h"

#include <vector>
#include <cassert>

#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\RenderTarget.hpp>

using Ptr = std::unique_ptr<SceneNode>;


SceneNode::SceneNode(Category::Typen category)
	: kinder()
	, parent(nullptr)
	, Kategory(category)
{}

void SceneNode::kindangehangt(Ptr child) {
	child->parent = this;
	kinder.push_back(std::move(child));
}

Ptr	SceneNode::detachChild(const SceneNode& node) {

	auto found = std::find_if(kinder.begin(), kinder.end(),
		[&](Ptr& p) {return p.get() == &node; });

	assert(found != kinder.end());

	Ptr res = std::move(*found);
	res->parent = nullptr;

	kinder.erase(found);

	return res;
}

sf::FloatRect SceneNode::ruckstossBekommenRechteck() const
{
	if (Kategory == Category::Typen::Fluss) {
		return sf::FloatRect(0.f, 0.f, 480.f, 320.f);
	}
}


void SceneNode::update(sf::Time dt, CommandQueue& commands) {
	aktuellesBild(dt, commands);
	kinderneuern(dt, commands);
}

sf::Vector2f SceneNode::weltPosition()	const {
	return weltTransformiert() * sf::Vector2f();
}

sf::Transform SceneNode::weltTransformiert() const {
	sf::Transform tx = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->parent) {
		tx = node->getTransform() * tx;
	}
	return tx;
}


void SceneNode::onCommand(const Kommando& command, sf::Time dt) {

	if (command.category & kategoryBekommen()) {
		command.action(*this, dt);
	}
	for (Ptr& c : kinder) {
		c->onCommand(command, dt);
	}
}

unsigned int SceneNode::kategoryBekommen() const {
	return Kategory;
}

void SceneNode::checkSceneCollision(SceneNode& node, std::set<Pair>& collisionPairs)
{
	checkNodeCollision(node, collisionPairs);

	for (Ptr& child : node.kinder)
		checkSceneCollision(*child, collisionPairs);
}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs)
{
	if (this != &node && istKolidiert(*this, node) && !zerstoert() && !node.zerstoert())
		collisionPairs.insert(std::minmax(this, &node));

	for (Ptr& child : kinder)
		child->checkNodeCollision(node, collisionPairs);
}

void SceneNode::kaputteEntfernen()
{
	auto wreckfieldBegin = std::remove_if(kinder.begin(), kinder.end(), std::mem_fn(&SceneNode::zumEntfernen)); 

	kinder.erase(wreckfieldBegin, kinder.end());

	std::for_each(kinder.begin(), kinder.end(), std::mem_fn(&SceneNode::kaputteEntfernen));
}

bool SceneNode::zumEntfernen() const
{
	return zerstoert();
}

bool SceneNode::zerstoert() const
{
	return false;
}

void SceneNode::aktuellesBild(sf::Time dt, CommandQueue& commands) {
}


void SceneNode::kinderneuern(sf::Time dt, CommandQueue& commands) {
	for (auto& child : kinder) {
		child->update(dt, commands);
	}

}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	aktuellezeichnen(target, states);
	kindZeichnen(target, states);
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::FloatRect rect = ruckstossBekommenRechteck();

	sf::RectangleShape shape;
	shape.setPosition(sf::Vector2f(rect.left, rect.top));
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(1.f);

	target.draw(shape);
}

void SceneNode::aktuellezeichnen(sf::RenderTarget& target, sf::RenderStates states) const {

}

void SceneNode::kindZeichnen(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& child : kinder) {
		child->draw(target, states);
	}
}


float distanzAusrechnen(const SceneNode& lhs, const SceneNode& rhs)
{
	return lange(lhs.weltPosition() - rhs.weltPosition());
}

bool istKolidiert(const SceneNode& lhs, const SceneNode& rhs)
{
	return lhs.ruckstossBekommenRechteck().intersects(rhs.ruckstossBekommenRechteck());
}
