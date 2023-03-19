#include "SpriteElemente.h"

SpriteNode::SpriteNode(const sf::Texture& texture)
	: sprite(texture)
{}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
	: sprite(texture, textureRect)
{}

void SpriteNode::aktuellezeichnen(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite, states);
}