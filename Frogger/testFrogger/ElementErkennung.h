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
	Hintergrund,
	Frogger,
	Leben,
	PinkerFrosch,
	Schlange
};

enum class FontID {
	Main
};

// Resourcen werden hier abgelagert in bei nutzung abgerufen

template <typename Resource, typename Identifier>
class ResourceHolder;
using TextureHolder_t = ResourceHolder<sf::Texture, TextureID>;
using FontHolder_t = ResourceHolder<sf::Font, FontID>;

