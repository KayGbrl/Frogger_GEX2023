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
        Frogger, Car1, Car2, Car3, Truck1, Truck2, Alligator, Turtle2, Turtle2_floating, Turtle3, Turtle3_floating, Log1, Log2, PinkFrog, Fly, Snake,
        FroggerWinner,
    };

    enum class State {
        IdleLeft,
        IdleRight,
        IdleUp,
        IdleDown,
        JumpLeft,
        JumpRight,
        JumpUp,
        JumpDown,
        Idle,
        Death,
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

    unsigned int    getCategory() const override;
    sf::FloatRect   getBoundingRect() const override;
    float           getSpeed() const;

    bool            isMarkedForRemoval() const override;
    void            setMarkedForRemoval(bool b);

    void            setState(State state);
    Arten::State    getState() const;

    void            setDirection(Arten::Direction d);
    Arten::Direction getDirection() const;

private:
    void            states();
    void            updateCurrent(sf::Time dt, CommandQueue& commands) override;
    void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    Type                                type_;
    State                               state_;
    mutable sf::Sprite                  sprite_;
    std::map<Arten::State, Animation>   animations_;
    Direction                           direction_;

    bool                                isMarkedForRemoval_;
};