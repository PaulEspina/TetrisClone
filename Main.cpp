#include <SFML/Graphics.hpp>
#include "Well.h"
#include "KeyManager.h"

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");
    window.setKeyRepeatEnabled(false);
    sf::Clock clock;
    KeyManager keyManager;

    Well well;
    Tetromino currentPiece(sf::Vector2i(0, 0), 1);

    while(window.isOpen())
    {
        // TICK
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            keyManager.update(event);
        }

        if(keyManager.isDown(sf::Keyboard::A))
        {
            currentPiece.move(sf::Vector2i(-1, 0));
            if(!well.inBounds(currentPiece))
            {
                currentPiece.move(sf::Vector2i(1, 0));
            }
        }
        if(keyManager.isDown(sf::Keyboard::D))
        {
            currentPiece.move(sf::Vector2i(1, 0));
            if(!well.inBounds(currentPiece))
            {
                currentPiece.move(sf::Vector2i(-1, 0));
            }
        }
        if(keyManager.isDown(sf::Keyboard::W))
        {
            currentPiece.move(sf::Vector2i(0, -1));
            if(!well.inBounds(currentPiece))
            {
                currentPiece.move(sf::Vector2i(0, 1));
            }
        }
        if(keyManager.isDown(sf::Keyboard::S))
        {
            currentPiece.move(sf::Vector2i(0, 1));
            if(!well.inBounds(currentPiece))
            {
                currentPiece.move(sf::Vector2i(0, -1));
            }
        }
        if(keyManager.isDown(sf::Keyboard::Q))
        {
            currentPiece.rotateCounterClockwise();
            keyManager.reset(sf::Keyboard::Q);
        }
        if(keyManager.isDown(sf::Keyboard::E))
        {
            currentPiece.rotateClockwise();
            keyManager.reset(sf::Keyboard::E);
        }
        if(keyManager.isDown(sf::Keyboard::C))
        {
            currentPiece.setType((currentPiece.getType() + 1) % 8);
            keyManager.reset(sf::Keyboard::C);
        }
        if(keyManager.isDown(sf::Keyboard::Space))
        {
            well.placePiece(currentPiece);
            keyManager.reset(sf::Keyboard::Space);
        }

        // UPDATE

        if(clock.getElapsedTime().asSeconds() > 1)
        {
            clock.restart();
            
            //currentPiece.move(sf::Vector2i(0, 1));
        }

        if(!well.inBounds(currentPiece))
        {
            well.findValidGrid(currentPiece);
        }
        well.showCurrentPiece(currentPiece);
        well.update();


        //DRAW

        window.clear();

        well.render(&window);

        window.display();
    }

    return 0;
}