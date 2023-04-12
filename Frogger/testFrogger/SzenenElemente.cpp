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
	: kinder_()
	, parent(nullptr)
	, Kategory_(category)
{}

void SceneNode::kindAnhenagen(Ptr child) {
	child->parent = this;
	kinder_.push_back(std::move(child));
}

Ptr	SceneNode::kindentfernen(const SceneNode& node) {

	auto found = std::find_if(kinder_.begin(), kinder_.end(),
		[&](Ptr& p) {return p.get() == &node; });

	assert(found != kinder_.end());

	Ptr res = std::move(*found);
	res->parent = nullptr;

	kinder_.erase(found);

	return res;
}

sf::FloatRect SceneNode::getBoundingRect() const
{
	if (Kategory_ == Category::Typen::Fluss) {
		return sf::FloatRect(0.f, 0.f, 480.f, 320.f);
	}
}


void SceneNode::update(sf::Time dt, CommandQueue& commands) {
	aktuellesBild(dt, commands);
	kinderneuern(dt, commands);
}

sf::Vector2f SceneNode::weltBekommen()	const {
	return weltAndern() * sf::Vector2f();
}

sf::Transform SceneNode::weltAndern() const {
	sf::Transform tx = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->parent) {
		tx = node->getTransform() * tx;
	}
	return tx;
}


void SceneNode::kommandAbgeben(const Kommando& command, sf::Time dt) {

	if (command.category & getCategory()) {
		command.action(*this, dt);
	}
	for (Ptr& c : kinder_) {
		c->kommandAbgeben(command, dt);
	}
}

unsigned int SceneNode::getCategory() const {
	return Kategory_;
}

void SceneNode::collisionInSzene(SceneNode& node, std::set<Pair>& collisionPairs)
{
	collisionKnoten(node, collisionPairs);

	for (Ptr& child : node.kinder_)
		collisionInSzene(*child, collisionPairs);
}

void SceneNode::collisionKnoten(SceneNode& node, std::set<Pair>& collisionPairs)
{
	if (this != &node && kolidiert(*this, node) && !zerstoert() && !node.zerstoert())
		collisionPairs.insert(std::minmax(this, &node));

	for (Ptr& child : kinder_)
		child->collisionKnoten(node, collisionPairs);
}

void SceneNode::kaputteEntfernen()
{
	auto wreckfieldBegin = std::remove_if(kinder_.begin(), kinder_.end(), std::mem_fn(&SceneNode::zumEntfernen));

	kinder_.erase(wreckfieldBegin, kinder_.end());

	std::for_each(kinder_.begin(), kinder_.end(), std::mem_fn(&SceneNode::kaputteEntfernen));
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
	for (auto& child : kinder_) {
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
	sf::FloatRect rect = getBoundingRect();

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
	for (auto& child : kinder_) {
		child->draw(target, states);
	}
}


float entfernungRechnen(const SceneNode& lhs, const SceneNode& rhs)
{
	return length(lhs.weltBekommen() - rhs.weltBekommen());
}

bool kolidiert(const SceneNode& lhs, const SceneNode& rhs)
{
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}
