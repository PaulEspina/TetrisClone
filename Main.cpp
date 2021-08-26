#include <SFML/Graphics.hpp>
#include "Well.h"

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");
    sf::Clock clock;

    Well well;
    Tetromino currentPience(sf::Vector2u(0, 0), 1, 0);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
            }
        }

        well.showCurrentPiece(currentPience);
        well.update();

        window.clear();

        well.render(&window);

        window.display();
    }

    return 0;
}