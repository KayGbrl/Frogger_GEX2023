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
    bool            zumEntfernen() const override;

    float           GeschwindigkeitMax() const;
    bool            SPielerZielErreicht() const;
    bool            vomAutoGetrofen() const;
    bool            insWasserGefallen() const;
    bool            aufSchwimmendeGegenr() const;

    void            alleZielegefullt();
    void            Zieleingenommen();
    void            zurusetzenFlagge();
    void            limitAufNull();
    int             scorebekommen();
    int             ueberbleibendeLeben();
    void            lebenAbziehen();
    void            respawnFrogger();

    void            statusSetzen(SpeilStatus state);
    Frogger::SpeilStatus  statusBekommen() const;

    sf::Time        getStateCountdown();

    void            imWasser(bool b);
    void            imWasserGestzt(bool b);
    void            spielerAufSchwimmendeGegner(bool b);
    void            punkteAufrechnen(int score);
    void            hop(Arten::Direction direction);

private:
    void            updateStates();
    void            aktuellesBild(sf::Time dt, CommandQueue& commands) override;
    void            aktuellezeichnen(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Arten::SpeilStatus                        status_;
    std::map<Arten::SpeilStatus, Animation>   animationen_;
    Direction                           richtung_;
    std::size_t                         richtungI_;
    sf::Time                            Status_;
    sf::Vector2f                        respawnPosition_;

    int                                 punktezahl_;
    int                                 Leben_;

    bool                                vomAutogetroffen;
    bool                                ImWasser;
    bool                                aufSchwimmendenGeggner_;
    bool                                zumEntfernen_;
    bool                                spielerImZielSpot_;
    bool                                zielGefuhllt_;

    mutable sf::Sprite                  bilder_;
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

