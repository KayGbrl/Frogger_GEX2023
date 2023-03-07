#include "Program.h"

#include "Spiel.h"
#include "StatenCheck.h"

#include "SpielStatus.h"
#include "Pause.h"
#include "ElementText.h"
#include "Menu.h"
#include "Verloren.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
    : window(sf::VideoMode(480, 600), "Frogger")
    , textures()
    , fonts()
    , player()
    , stateStack(State::Context(window, textures, fonts, player))
    , statsText()
    , statsUpdateTime()
    , statsNumFrames(0){

    window.setKeyRepeatEnabled(false);

    fonts.load(FontID::Main, "Media/Sansation.ttf");

    textures.load(TextureID::TitleScreen, "Media/Textures/Placeholder.png");
    statsText.setFont(fonts.get(FontID::Main));
    statsText.setPosition(5.f, 5.f);
    statsText.setCharacterSize(10u);

    registerStates();
    stateStack.pushState(StateID::Title);
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);

            if (stateStack.isEmpty())
                window.close();
        }

        render();
    }
}

void Application::processInput()
{

    sf::Event event;
    while (window.pollEvent(event))
    {
        stateStack.handleEvent(event);

        if (event.type == sf::Event::Closed)
            window.close();
    }

}

void Application::update(sf::Time dt)
{
    stateStack.update(dt);
}

void Application::render()
{
    window.clear();
    stateStack.draw();

    window.setView(window.getDefaultView());
    window.draw(statsText);
    window.display();
}


void Application::registerStates()
{
    stateStack.registerState<TitleState>(StateID::Title);
    stateStack.registerState<MenuState>(StateID::Menu);
    stateStack.registerState<GameState>(StateID::Game);
    stateStack.registerState<PauseState>(StateID::Pause);
    stateStack.registerState<GameOverState>(StateID::GameOverState);
}
