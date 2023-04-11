#pragma once

#include "Spiel.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <string>
#include <memory>
#include <cassert>
#include <map>
#include <stdexcept>

template <typename R, typename Id>
class ResourceHolder
{

public:
	void					laden(Id id, const std::string& filename);

	template <typename P>
	void					laden(Id id, const std::string& filename, const P& secondParameter);


	const R& get(Id id) const;
	R& get(Id id);

private:
	void					insertResource(Id id, std::unique_ptr<R> resource);

private:
	std::map<Id, std::unique_ptr<R> > resourceMap;
};

template <typename R, typename Id>
void ResourceHolder<R, Id>::laden(Id id, const std::string& filename) {

	std::unique_ptr<R> resource(new R());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("Elemente - Failed to load " + filename);

	insertResource(id, std::move(resource));
}


template <typename R, typename Id>
template <typename P>
void ResourceHolder<R, Id>::laden(Id id, const std::string& filename, const P& secondParam) {

	std::unique_ptr<R> resource(new R());
	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("Elemente - Failed to load " + filename);

	insertResource(id, std::move(resource));
}


template <typename R, typename Id>
R& ResourceHolder<R, Id>::get(Id id) {
	auto found = resourceMap.find(id);
	assert(found != resourceMap.end());

	return *found->second;
}


template <typename R, typename Id>
const R& ResourceHolder<R, Id>::get(Id id) const {
	auto found = resourceMap.find(id);
	assert(found != resourceMap.end());

	return *found->second;
}


template <typename R, typename Id>
void ResourceHolder<R, Id>::insertResource(Id id, std::unique_ptr<R> resource)
{
	auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);
	virtual void	draw() override;
	virtual bool	aktualisieren(sf::Time dt) override;
	virtual bool	ereiknissHandeln(const sf::Event& event) override;

private:
	sf::Sprite		hintergrundBild;
	sf::Text		text;

	bool			textZeigen;
	sf::Time		textEffekte;
};

//Zuffals system
namespace zufall
{
	class Sprite;
	class Text;
}

class Animation;

void			zentrierterPunkt(sf::Sprite& sprite);
void			zentrierterPunkt(sf::Text& text);


float			mass(float radian);
float			radiant(float degree);
float			lange(sf::Vector2f v);
sf::Vector2f	normalisieren(sf::Vector2f v);
int				zuffalsZahl(int exclusiveMax);

sf::IntRect		drehen(const sf::IntRect& rec);
