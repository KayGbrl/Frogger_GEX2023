#include "Text.h"

#include <SFML/Graphics/RenderTarget.hpp>

TextNode::TextNode(const FontHolder_t& fonts, const std::string& text_)
	:SceneNode(Category::Punkte)
{
	text.setFont(fonts.get(FontID::Main));
	text.setCharacterSize(30);
	setString(text_);
}

void TextNode::setString(const std::string& text_)
{
	text.setString(text_);
	zentrierterPunkt(text);
}

void TextNode::aktuellezeichnen(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text, states);
}
