#pragma once

namespace sf
{
	class Texture;
	class Font;
	class SoundBuffer;
}

enum class TextureID
{
	TitleScreen,
	Background,
	Frogger,
	Live,
	PinkFrog,
	Snake
};

enum class FontID {
	Main
};

template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder_t = ResourceHolder<sf::Texture, TextureID>;
using FontHolder_t = ResourceHolder<sf::Font, FontID>;

