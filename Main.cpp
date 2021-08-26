#include <SFML/Graphics.hpp>

#include "Block.h"
#include "Well.h"
#include "Tetromino.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");

    Well well(sf::Vector2f(0, 0));
    Block block0(sf::Vector2u(0, 0), 0);
    Block block1(sf::Vector2u(0, 1), 1);
    Block block2(sf::Vector2u(0, 2), 2);
    Block block3(sf::Vector2u(0, 3), 3);
    // Block block4(sf::Vector2u(0, 4), 4, well.getBlockSize());
    // Block block5(sf::Vector2u(0, 5), 5, well.getBlockSize());

     well.addBlock(&block0);
     well.addBlock(&block1);
     well.addBlock(&block2);
     well.addBlock(&block3);
    // well.addBlock(&block4);
    // well.addBlock(&block5);

    //Block blocks[4] ={ Block(sf::Vector2u(0, 0), 0, well.getBlockSize()),
    //                   Block(sf::Vector2u(0, 1), 0, well.getBlockSize()),       
    //                   Block(sf::Vector2u(0, 2), 0, well.getBlockSize()),
    //                   Block(sf::Vector2u(0, 3), 0, well.getBlockSize())};

    //for(Block block : blocks)
    //{
    //    well.addBlock(&block);
    //}

    //Tetromino tetromino(blocks, sizeof(blocks) / sizeof(blocks[0]));

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
                    //tetromino.fall();
                }
            }
        }

        //for(Block block : blocks)
        //{
        //    block.update();
        //}

        //block0.update();
        //block1.update();
        //block2.update();
        //block3.update();
        // block4.update();
        // block5.update();


        window.clear();

        well.draw(window);

        window.display();
    }

    return 0;
}