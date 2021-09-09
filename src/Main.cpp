#include <SFML/Graphics.hpp>

#include "Game.h"

const unsigned int TICKPERSECOND = 60;

int main()
{
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tetris");
    window.setKeyRepeatEnabled(false);
    
    MovementTimer moveTimer(1.0f, 0.25f, 0.25f, 25, 20);
    Game game(moveTimer);
    KeyManager keyManager;

    while(window.isOpen())
    {
        if(game.isGameOver())
        {
            game.init();
        }
        sf::Event event;
        keyManager.prepare();
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            keyManager.update(event);
        }
        game.tick(keyManager);
        if(clock.getElapsedTime().asMilliseconds() > (1000 / TICKPERSECOND))
        {
            game.update();
            clock.restart();
        }
        game.render(window);
    }
    return 0;
}