#include "Game.h"

Game::Game(MovementSettings &movSettings)
{
    this->movSettings = &movSettings;
    init();
}

void Game::init()
{
    srand((unsigned int) time(0));
    currentPiece = Tetromino(pieceMan.next());
    well = Well(sf::Vector2f(50, 50));
    movSettings->init();
}

void Game::tick(KeyManager &keyManager)
{
    auto moveLeft = [](Tetromino &currentPiece, Well &well)
    {
        currentPiece.move(sf::Vector2i(-1, 0));
        if(!well.inBounds(currentPiece))
        {
            currentPiece.move(sf::Vector2i(1, 0));
        }
    };
    auto moveRight = [](Tetromino &currentPiece, Well &well)
    {
        currentPiece.move(sf::Vector2i(1, 0));
        if(!well.inBounds(currentPiece))
        {
            currentPiece.move(sf::Vector2i(-1, 0));
        }
    }; 
    auto moveDown = [](Tetromino &currentPiece, Well &well)
    {
        currentPiece.move(sf::Vector2i(0, 1));
        if(!well.inBounds(currentPiece))
        {
            currentPiece.setAtBottom(true);
            currentPiece.move(sf::Vector2i(0, -1));
        }
    };

    if(keyManager.isPressed(sf::Keyboard::Left))
    {
        moveLeft(currentPiece, well);
        movSettings->restartMoveTimer();
        movSettings->restartDASTimer();
    }
    if(keyManager.isDown(sf::Keyboard::Left))
    {
        if(movSettings->shouldDAS() && movSettings->shouldMove())
        {
            moveLeft(currentPiece, well);
            movSettings->restartMoveTimer();
        }
    }
    if(keyManager.isPressed(sf::Keyboard::Right))
    {
        moveRight(currentPiece, well);
        movSettings->restartMoveTimer();
        movSettings->restartDASTimer();
    }
    if(keyManager.isDown(sf::Keyboard::Right))
    {
        if(movSettings->shouldDAS() && movSettings->shouldMove())
        {
            moveRight(currentPiece, well);
            movSettings->restartMoveTimer();
        }
    }
    if(keyManager.isPressed(sf::Keyboard::Down))
    {
        currentPiece.setDropLock(true);
    }
    if(keyManager.isDown(sf::Keyboard::Down))
    {
        if(!currentPiece.isAtBottom())
        {
            if(movSettings->shouldSoftDrop())
            {
                moveDown(currentPiece, well);
                movSettings->restartSoftDropTimer();
            }
            movSettings->restartFallTimer();
        }
    }
    if(keyManager.isReleased(sf::Keyboard::Down))
    {
        currentPiece.setDropLock(false);
    }
    if(keyManager.isPressed(sf::Keyboard::LControl))
    {
        currentPiece.rotateCounterClockwise();
        if(!currentPiece.isAtBottom() && movSettings->shouldSoftDrop())
        {
            movSettings->restartSoftDropTimer();
        }
        movSettings->restartFallTimer();
    }
    if(keyManager.isPressed(sf::Keyboard::Up))
    {
        currentPiece.rotateClockwise();
        if(!currentPiece.isAtBottom() && movSettings->shouldSoftDrop())
        {
            movSettings->restartSoftDropTimer();
        }
        movSettings->restartFallTimer();
    }
    if(keyManager.isPressed(sf::Keyboard::LShift))
    {
        pieceMan.swap(currentPiece);
        if(!currentPiece.isAtBottom() && movSettings->shouldSoftDrop())
        {
            movSettings->restartSoftDropTimer();
        }
        movSettings->restartFallTimer();
    }
    if(keyManager.isPressed(sf::Keyboard::Space))
    {
        dropPiece();
    }
    if(keyManager.isPressed(sf::Keyboard::R))
    {
        well.init();
        pieceMan.init();
        currentPiece = Tetromino(pieceMan.next());
        movSettings->restartFallTimer();
    }
}

void Game::update()
{
    if(!currentPiece.isAtBottom() && movSettings->shouldFall())
    {
        currentPiece.move(sf::Vector2i(0, 1));
        if(!well.inBounds(currentPiece))
        {
            currentPiece.setAtBottom(true);
            currentPiece.move(sf::Vector2i(0, -1));
        }
        else
        {
            movSettings->restartFallTimer();
        }
    }

    if(currentPiece.isAtBottom())
    {
        if(movSettings->shouldLock() || (!currentPiece.shouldLock() && movSettings->shouldFall()))
        {
            dropPiece();
            movSettings->restartLockTimer();
        }
        else
        {
            if(movSettings->isLockTimerRunning())
            {
                movSettings->stopLockTimer();
            }
            movSettings->runLockTimer();
        }
    }
    else
    {
        movSettings->setLockTimerRunning(false);
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

void Game::dropPiece()
{
    well.dropCurrentPiece();
    currentPiece = Tetromino(pieceMan.next());
    movSettings->restartFallTimer();
}