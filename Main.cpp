#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tetris");
    window.setKeyRepeatEnabled(false);
    
    MovementSettings movSettings(2.0f, 0.5f, 0.2f, 20, 20);
    Game game(movSettings);
    KeyManager keyManager;

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