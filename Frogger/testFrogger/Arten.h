#pragma once

#include "Entity.h"
#include "Elemente.h"
#include "ElementErkennung.h"
#include "Animation.h"
#include "Ausloser.h"

#include <SFML/Graphics/Sprite.hpp>

class Arten : public Entity
{
public:
    enum class Type {
        Frogger, Gelbesauto, Gruenesauto, Pinkesauto, Traktor, Lkw, Alligator, Zweierkroete, Zweierkroete_Untertauchen, Dreierkroete, Dreierkroete_Untertauchen, Kleinerstamm, Grosserstamm, Pinkerfrosh, Schlange, Fliege,
        FroggerWinner,
    };

    enum class SpeilStatus {
        Stehenlinks,
        Stehenrechts,
        Stehenhoch,
        Stehenrunter,
        Links,
        Rechts,
        Hoch,
        Runter,
        Still,
        Tod,
        Respawn,
        count,
        GameOver
    };

    enum class Direction
    {
        Left, Right, Up, Down
    };


public:
    Arten(Type type, const TextureHolder_t& textures, const FontHolder_t& fonts);
    Arten(const TextureHolder_t& textures, const FontHolder_t& fonts);
    ~Arten() = default;

    unsigned int          getCategory() const override;
    sf::FloatRect         getBoundingRect() const override;
    float                 speed() const;

    bool                  zumEntfernen() const override;
    void                  setMarkedForRemoval(bool b);

    void                  Statussetzen(SpeilStatus state);
    Arten::SpeilStatus    StatusGeben() const;

    void                  RichtungSetzen(Arten::Direction d);
    Arten::Direction      RichtungGEebn() const;

private:
    void            states();
    void            aktuellesBild(sf::Time dt, CommandQueue& commands) override;
    void            aktuellezeichnen(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    Type                                      typen;
    SpeilStatus                               status;
    mutable sf::Sprite                        sprite_;
    std::map<Arten::SpeilStatus, Animation>   animationen;
    Direction                                 richtungen;

    bool                                      isMarkedForRemoval_;
};