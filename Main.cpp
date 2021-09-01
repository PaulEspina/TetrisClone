#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
    Game game;
    KeyManager keyManager;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tetris");
    window.setKeyRepeatEnabled(false);

    while(window.isOpen())
    {
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
        game.update();
        game.render(window);
    }

    return 0;
}