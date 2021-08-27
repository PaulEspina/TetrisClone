#include <SFML/Graphics.hpp>
#include "Well.h"

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");
    sf::Clock clock;

    Well well;
    Tetromino currentPiece(sf::Vector2i(0, 0), 6);

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
            if(event.type == sf::Event::KeyPressed)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    currentPiece.move(sf::Vector2i(-1, 0));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    currentPiece.move(sf::Vector2i(1, 0));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    currentPiece.move(sf::Vector2i(0, -1));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    currentPiece.move(sf::Vector2i(0, 1));
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                {
                    currentPiece.rotateCounterClockwise();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                {
                    currentPiece.rotateClockwise();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                {
                    currentPiece.setType((currentPiece.getType() + 1) % 8);
                }
            }
        }

        // UPDATE

        //if(clock.getElapsedTime().asSeconds() > 1)
        //{
        //    clock.restart();
        //    currentPiece.move(sf::Vector2i(0, 1));
        //}

        well.showCurrentPiece(currentPiece);
        well.update();


        //DRAW

        window.clear();

        well.render(&window);

        window.display();
    }

    return 0;
}