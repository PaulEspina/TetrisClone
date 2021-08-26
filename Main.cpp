#include <SFML/Graphics.hpp>

#include "Block.h"
#include "Well.h"
#include "Tetromino.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");
    Well well(sf::Vector2f(0, 0));
    Block block0(sf::Vector2u(0, 0), 0, well.getBlockSize());
    Block block1(sf::Vector2u(0, 1), 1, well.getBlockSize());
    Block block2(sf::Vector2u(0, 2), 2, well.getBlockSize());
    Block block3(sf::Vector2u(0, 3), 3, well.getBlockSize());
    // Block block4(sf::Vector2u(0, 4), 4, well.getBlockSize());
    // Block block5(sf::Vector2u(0, 5), 5, well.getBlockSize());

    // well.addBlock(&block0);
    // well.addBlock(&block1);
    // well.addBlock(&block2);
    // well.addBlock(&block3);
    // well.addBlock(&block4);
    // well.addBlock(&block5);

    Block blocks[4] ={ block0, block1, block2, block3 };

    well.addBlock(&block0);
    well.addBlock(&block1);
    well.addBlock(&block2);
    well.addBlock(&block3);

    Tetromino tetromino(blocks, sizeof(blocks) / sizeof(blocks[0]));

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
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    // block0.setGridPos(sf::Vector2u(block0.getGridPos().x, block0.getGridPos().y + 1));
                    tetromino.fall();
                }
            }
        }

        block0.update();
        block1.update();
        block2.update();
        block3.update();
        // block4.update();
        // block5.update();


        window.clear();

        well.draw(window);

        window.display();
    }

    return 0;
}