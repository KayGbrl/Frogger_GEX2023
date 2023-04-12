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

    bool            zumEntfernen() const override;

    void            hatFroggerZielGefulltsetzen();
    bool            froggerhatZielErreicht() const;

    void            istImZiel();

    void            setState(SpeilStatus state);
    Frogger::SpeilStatus  getState() const;

    bool            vomAutoGetriffen() const;
    void            vomAutiGetroffenFestsetzen(bool b);
    bool            imFluss() const;
    void            imFlussFestgesetzt(bool b);
    bool            aufSchwimmendenGegener() const;
    void            spieleraufSchwimmendenGegener(bool b);

    void            zuruscksetzenPosition();

    void            zeitStatusSetzen();
    sf::Time        zeitStatusbekommen();

    int             punktezahlBekommen();
    void            punktezahldDraufrechnen(int score);

    int             lebenUbrigBekommen();
    void            lebenReduzieren();

    void            hop(Arten::Direction direction);

    void            respawnFrogger();

private:
    void            updateStates();
    void            aktuellesBild(sf::Time dt, CommandQueue& commands) override;
    void            aktuellezeichnen(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Arten::SpeilStatus                        status_;
    mutable sf::Sprite                        sprite_;
    std::map<Arten::SpeilStatus, Animation>   animationen_;
    Direction                                 richtungen_;

    std::size_t                         richtungIndex_;
    sf::Time                            stateCountdown_;

    sf::Vector2f                        respawnPosition_;
    bool                                vomAutoGetroffen_;
    bool                                imFluss_;
    bool                                aufSchwimmendenGegner_;

    int                                 punkteZahl_;
    int                                 lebenUbrig_;
    bool                                zumEnfernenMarkiet_;
    bool                                hatSpielerspotgefullt_;
    bool                                zielGebietGefullt_;
};

//Hauptmenu
class Menu : public State
{

public:
    Menu(StateStack& stack, Context context);

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
    virtual bool		update(sf::Time dt) override;
    virtual bool		handleEvent(const sf::Event& event) override;

private:
    sf::Sprite			hintergrungSprite;
    sf::Text			pauseText;
    sf::Text			hilfeText;

};

