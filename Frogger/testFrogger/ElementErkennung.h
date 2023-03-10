
#pragma once

namespace sf
{
	class Texture;
	class Font;
	/*class Shader;*/
	class SoundBuffer;
}

enum class TextureID
{
	TitleScreen,
	Background,
	Frogger,
	Live,
	PinkFrog
};

enum class FontID {
	Main
};

template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder_t = ResourceHolder<sf::Texture, TextureID>;
using FontHolder_t = ResourceHolder<sf::Font, FontID>;

