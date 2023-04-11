#include "Program.h"

#include "Spiel.h"
#include "StatenCheck.h"
#include "SpielStatus.h"
#include "ElementText.h"
#include "Verloren.h"

#include "SpriteElemente.h"

const sf::Time Application::zeitImFrame = sf::seconds(1.f / 60.f);

Application::Application()
    : fenster(sf::VideoMode(480, 600), "Frogger")
    , texturen()
    , fonts()
    , spieler()
    , statusStaffelung(State::Context(fenster, texturen, fonts, spieler))
    , textStatus()
    , zeitDerStaten()
    , statusDerFrames(0){

    fenster.setKeyRepeatEnabled(false);

    fonts.laden(FontID::Main, "Media/Sansation.ttf");

    texturen.laden(TextureID::TitleScreen, "Media/Textures/FrogerMain.png");
    textStatus.setFont(fonts.get(FontID::Main));
    textStatus.setPosition(5.f, 5.f);
    textStatus.setCharacterSize(10u);

    Statusregistrieren();
    statusStaffelung.stapelAbgeben(StateID::Title);
}

void Application::starten()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (fenster.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > zeitImFrame) {
            timeSinceLastUpdate -= zeitImFrame;

            eingabe();
            update(zeitImFrame);

            if (statusStaffelung.istLeer())
                fenster.close();
        }

        rendern();
    }
}

void Application::eingabe()
{

    sf::Event event;
    while (fenster.pollEvent(event))
    {
        statusStaffelung.handleEvent(event);

        if (event.type == sf::Event::Closed)
            fenster.close();
    }

}

void Application::update(sf::Time dt)
{
    statusStaffelung.aktualisiren(dt);
}

void Application::rendern()
{
    fenster.clear();
    statusStaffelung.zeichnen();

    fenster.setView(fenster.getDefaultView());
    fenster.draw(textStatus);
    fenster.display();
}


void Application::Statusregistrieren()
{
    statusStaffelung.statusRegistrieren<TitleState>(StateID::Title);
    statusStaffelung.statusRegistrieren<Menu>(StateID::Menu);
    statusStaffelung.statusRegistrieren<GameState>(StateID::Game);
    statusStaffelung.statusRegistrieren<Pause>(StateID::Pause);
    statusStaffelung.statusRegistrieren<GameOverState>(StateID::GameOverState);
}
