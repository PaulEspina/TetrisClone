#include "Game.h"

Game::Game()
{
    srand((unsigned int) time(0));
    currentPiece = Tetromino(pieceMan.next());
    atBottom = false;
    well = Well(sf::Vector2f(50, 50));
}

void Game::tick(KeyManager &keyManager)
{
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
        if(atBottom)
        {
            atBottom = false;
            well.dropCurrentPiece();
            currentPiece = Tetromino(pieceMan.next());
        }
        else
        {
            currentPiece.move(sf::Vector2i(0, 1));
            if(!well.inBounds(currentPiece))
            {
                atBottom = true;
                currentPiece.move(sf::Vector2i(0, -1));
            }
            dropTimer.restart();
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
        pieceMan.swap(currentPiece);
    }
    if(keyManager.isPressed(sf::Keyboard::Space))
    {
        atBottom = false;
        well.dropCurrentPiece();
        currentPiece = Tetromino(pieceMan.next());
    }
    if(keyManager.isPressed(sf::Keyboard::R))
    {
        well.init();
        pieceMan.init();
        currentPiece = Tetromino(pieceMan.next());
        dropTimer.restart();
    }
}

void Game::update()
{
    if(!atBottom && dropTimer.getElapsedTime().asSeconds() > 0.5)
    {
        currentPiece.move(sf::Vector2i(0, 1));
        if(!well.inBounds(currentPiece))
        {
            currentPiece.move(sf::Vector2i(0, -1));
            atBottom = true;
        }
        else
        {
            dropTimer.restart();
        }
    }

    if(atBottom && dropTimer.getElapsedTime().asSeconds() > 2)
    {
        well.dropCurrentPiece();
        currentPiece = Tetromino(pieceMan.next());
        atBottom = false;
        dropTimer.restart();
    }

    if(!well.inBounds(currentPiece))
    {
        well.findValidGrid(currentPiece);
    }
    well.previewDrop(currentPiece);
    well.showCurrentPiece(currentPiece);
    well.update();
}

void Game::render(sf::RenderWindow &window)
{
    window.clear();

    well.render(&window);

    window.display();
}