#include <SFML/Graphics.hpp>
#include "Well.h"
#include "KeyManager.h"
#include <cstdlib>
#include <time.h>

int main()
{
    srand((unsigned int) time(0));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");
    window.setKeyRepeatEnabled(false);
    sf::Clock clock;
    KeyManager keyManager;

    Well well(sf::Vector2f(50, 50));
    Tetromino currentPiece(rand() % 7 + 1);

    while(window.isOpen())
    {
        // TICK
        sf::Event event;
        keyManager.init();
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            keyManager.update(event);
        }

        /*if(keyManager.isDown(sf::Keyboard::Left))
        {
            currentPiece.move(sf::Vector2i(-1, 0));
            if(!well.inBounds(currentPiece))
            {
                currentPiece.move(sf::Vector2i(1, 0));
            }
        }
        if(keyManager.isDown(sf::Keyboard::Right))
        {
            currentPiece.move(sf::Vector2i(1, 0));
            if(!well.inBounds(currentPiece))
            {
                currentPiece.move(sf::Vector2i(-1, 0));
            }
        }
        if(keyManager.isDown(sf::Keyboard::Down))
        {
            currentPiece.move(sf::Vector2i(0, 1));
            if(!well.inBounds(currentPiece))
            {
                currentPiece.move(sf::Vector2i(0, -1));
            }
        }*/
        if(keyManager.isPressed(sf::Keyboard::Left))
        {
            currentPiece.move(sf::Vector2i(-1, 0));
            if(!well.inBounds(currentPiece))
            {
                currentPiece.move(sf::Vector2i(1, 0));
            }
        }
        if(keyManager.isPressed(sf::Keyboard::Right))
        {
            currentPiece.move(sf::Vector2i(1, 0));
            if(!well.inBounds(currentPiece))
            {
                currentPiece.move(sf::Vector2i(-1, 0));
            }
        }
        if(keyManager.isPressed(sf::Keyboard::Down))
        {
            currentPiece.move(sf::Vector2i(0, 1));
            if(!well.inBounds(currentPiece))
            {
                currentPiece.move(sf::Vector2i(0, -1));
            }
        }
        if(keyManager.isPressed(sf::Keyboard::LControl))
        {
            currentPiece.rotateCounterClockwise();
        }
        if(keyManager.isPressed(sf::Keyboard::Up))
        {
            currentPiece.rotateClockwise();
        }
        if(keyManager.isPressed(sf::Keyboard::LShift))
        {
            currentPiece.setType((currentPiece.getType() + 1) % 7 + 1);
        }
        if(keyManager.isPressed(sf::Keyboard::Space))
        {
            well.dropCurrentPiece();
            currentPiece = Tetromino(rand() % 7 + 1);
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
        well.previewDrop(currentPiece);
        well.showCurrentPiece(currentPiece);
        well.update();


        //DRAW

        window.clear();

        well.render(&window);

        window.display();
    }

    return 0;
}