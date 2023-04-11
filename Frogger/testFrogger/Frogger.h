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

    unsigned int    kategoryBekommen() const override;
    sf::FloatRect   ruckstossBekommenRechteck() const override;
    float           getMaxSpeed() const;

    bool            zumEntfernen() const override;

    void            setHasFroggerFilledSlots();
    bool            hasFroggerFilledSlots() const;

    void            setIsWinningSpotTaken();

    void            setState(SpeilStatus state);
    Frogger::SpeilStatus  getState() const;

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
    void            aktuellesBild(sf::Time dt, CommandQueue& commands) override;
    void            aktuellezeichnen(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Arten::SpeilStatus                        state_;
    mutable sf::Sprite                  sprite_;
    std::map<Arten::SpeilStatus, Animation>   animations_;
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
class Menu : public State
{

public:
    Menu(StateStack& stack, Context context);

    virtual void	draw() override;
    virtual bool	aktualisieren(sf::Time dt) override;
    virtual bool	ereiknissHandeln(const sf::Event& event) override;

    void			updateOptionText();

private:
    enum OptionNames {
        Play = 0,
        Exit = 1,
    };

private:
    sf::Sprite				hintergrund;

    std::vector<sf::Text>	optionen;
    std::size_t				optionIndex;

};

//Pause Menu
class Pause :
    public State
{
public:
    Pause(StateStack& stack, Context context);

    virtual void		draw() override;
    virtual bool		aktualisieren(sf::Time dt) override;
    virtual bool		ereiknissHandeln(const sf::Event& event) override;

private:
    sf::Sprite			hintergrungSprite;
    sf::Text			pauseText;
    sf::Text			hilfeText;

};

