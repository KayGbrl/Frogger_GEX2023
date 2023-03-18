#pragma once

#include "Arten.h"

#include "Spiel.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>



class Frogger : public Arten
{
public:

    enum class Direction
    {
        Left, Right, Up, Down
    };


public:
    Frogger(const TextureHolder_t& textures, const FontHolder_t& fonts);
    ~Frogger() = default;

    unsigned int    getCategory() const override;
    sf::FloatRect   getBoundingRect() const override;
    float           getMaxSpeed() const;

    bool            isMarkedForRemoval() const override;

    void            setHasFroggerFilledSlots();
    bool            hasFroggerFilledSlots() const;

    void            setIsWinningSpotTaken();

    void            setState(State state);
    Frogger::State  getState() const;

    bool            isStruckByCar() const;
    void            setIsStruckByCar(bool b);
    bool            isInRiver() const;
    void            setIsInRiver(bool b);
    bool            isOnSwimmingNPC() const;
    void            playerOnSwimmingNPC(bool b);

    void            resetPositionFlags();

    void            setStateCountdownToZero();
    sf::Time        getStateCountdown();

    int             getScore();
    void            addScore(int score);

    int             getLivesLeft();
    void            deductLife();

    void            hop(Arten::Direction direction);

    void            respawnFrogger();

private:
    void            updateStates();
    void            updateCurrent(sf::Time dt, CommandQueue& commands) override;
    void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Arten::State                        state_;
    mutable sf::Sprite                  sprite_;
    std::map<Arten::State, Animation>   animations_;
    Direction                           direction_;

    std::size_t                         directionIndex_;
    sf::Time                            stateCountdown_;

    sf::Vector2f                        respawnPosition_;
    bool                                isStruckByCar_;
    bool                                isInRiver_;
    bool                                isOnSwimmingNPC_;

    int                                 score_;
    int                                 livesLeft_;
    bool                                isMarkedForRemoval_;
    bool                                hasFroggerFilledSlots_;
    bool                                isWinningSpotTaken_;
};

//Hauptmenu
class MenuState : public State
{

public:
    MenuState(StateStack& stack, Context context);

    virtual void	draw() override;
    virtual bool	update(sf::Time dt) override;
    virtual bool	handleEvent(const sf::Event& event) override;

    void			updateOptionText();

private:
    enum OptionNames {
        Play = 0,
        Exit = 1,

    };

private:
    sf::Sprite				backgroundSprite;

    std::vector<sf::Text>	options;
    std::size_t				optionIndex;

};

//Pause Menu
class PauseState :
    public State
{
public:
    PauseState(StateStack& stack, Context context);

    virtual void		draw() override;
    virtual bool		update(sf::Time dt) override;
    virtual bool		handleEvent(const sf::Event& event) override;

private:
    sf::Sprite			hintergrungSprite;
    sf::Text			pauseText;
    sf::Text			hilfeText;

};

