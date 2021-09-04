#include "Game.h"

Game::Game(MovementTimer &moveTimer)
{
    this->moveTimer = &moveTimer;
    pieceMan = PieceManager(1);
    init();
}

void Game::init()
{
    srand((unsigned int) time(0));
    gameOver = false;
    currentPiece = Tetromino(pieceMan.next());
    well = Well(sf::Vector2f(50, 50));
    moveTimer->init();
    well.init();
    pieceMan.init();
    currentPiece = Tetromino(pieceMan.next());
    holdBox = PieceBox(sf::Vector2f(350, 500), 25);
    holdBox.init();
    bag = Bag(sf::Vector2f(350, 125), pieceMan, 5, 15);
    bag.init();
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
        moveTimer->restartMoveTimer();
        moveTimer->restartDASTimer();
        currentPiece.setDropLock(true);
    }
    if(keyManager.isDown(sf::Keyboard::Left))
    {
        if(moveTimer->shouldDAS() && moveTimer->shouldMove())
        {
            moveLeft(currentPiece, well);
            moveTimer->restartMoveTimer();
        }
        if(currentPiece.isAtBottom())
        {
            moveTimer->restartFallTimer();
        }
    }
    if(keyManager.isReleased(sf::Keyboard::Right))
    {
        currentPiece.setDropLock(false);
    }
    if(keyManager.isPressed(sf::Keyboard::Right))
    {
        moveRight(currentPiece, well);
        moveTimer->restartMoveTimer();
        moveTimer->restartDASTimer();
        currentPiece.setDropLock(true);
    }
    if(keyManager.isDown(sf::Keyboard::Right))
    {
        if(moveTimer->shouldDAS() && moveTimer->shouldMove())
        {
            moveRight(currentPiece, well);
            moveTimer->restartMoveTimer();
        }
        if(currentPiece.isAtBottom())
        {
            moveTimer->restartFallTimer();
        }
    }
    if(keyManager.isReleased(sf::Keyboard::Right))
    {
        currentPiece.setDropLock(false);
    }
    if(keyManager.isPressed(sf::Keyboard::Down))
    {
        currentPiece.setDropLock(true);
    }
    if(keyManager.isDown(sf::Keyboard::Down))
    {
        if(moveTimer->shouldSoftDrop())
        {
            moveDown(currentPiece, well);
            moveTimer->restartSoftDropTimer();
        }
        moveTimer->restartFallTimer();
    }
    if(keyManager.isReleased(sf::Keyboard::Down))
    {
        currentPiece.setDropLock(false);
    }
    if(keyManager.isPressed(sf::Keyboard::LControl))
    {
        currentPiece.rotateCounterClockwise();
        moveTimer->restartFallTimer();
        moveTimer->setLockTimerRunning(true);
    }
    if(keyManager.isPressed(sf::Keyboard::Up))
    {
        currentPiece.rotateClockwise();
        moveTimer->restartFallTimer();
        moveTimer->setLockTimerRunning(true);
    }
    if(keyManager.isPressed(sf::Keyboard::LShift))
    {
        pieceMan.swap(currentPiece);
        holdBox.setPieceType(pieceMan.getHold());
        if(!currentPiece.isAtBottom() && moveTimer->shouldSoftDrop())
        {
            moveTimer->restartSoftDropTimer();
        }
        moveTimer->restartFallTimer();
    }
    if(keyManager.isPressed(sf::Keyboard::Space))
    {
        dropPiece();
        pieceMan.resetHoldRepeat();
    }
    if(keyManager.isPressed(sf::Keyboard::R))
    {
        init();
    }
}

void Game::update()
{
    holdBox.update();
    bag.update();

    if(!gameOver)
    {
        if(well.getOccupiedHeight() > well.getWellHeight())
        {
            gameOver = true;
        }

        currentPiece.move(sf::Vector2i(0, 1));
        if(!well.inBounds(currentPiece))
        {
            currentPiece.setAtBottom(true);
        }
        else
        {
            currentPiece.setAtBottom(false);
        }
        currentPiece.move(sf::Vector2i(0, -1));

        if(moveTimer->shouldFall() && !currentPiece.isAtBottom())
        {
            currentPiece.move(sf::Vector2i(0, 1));
            moveTimer->restartFallTimer();
        }

        if(currentPiece.isAtBottom())
        {
            if(moveTimer->shouldLock())
            {
                dropPiece();
                moveTimer->restartLockDelay();
            }
            else
            {
                if(moveTimer->isLockTimerRunning())
                {
                    moveTimer->updateLockTimer();
                }
                else
                {
                    moveTimer->setLockTimerRunning(true);
                    moveTimer->restartLockDelay();
                }
            }
        }
        else
        {
            moveTimer->setLockTimerRunning(false);
        }

        if(!well.inBounds(currentPiece))
        {
            well.findValidGrid(currentPiece);
        }
        well.previewDrop(currentPiece);
        well.showCurrentPiece(currentPiece);
        well.update();
    }
}

void Game::render(sf::RenderWindow &window)
{
    window.clear();

    well.render(window);
    holdBox.render(window);
    bag.render(window);

    window.display();
}

bool Game::isGameOver()
{
    return gameOver;
}

void Game::dropPiece()
{
    well.dropCurrentPiece();
    currentPiece = Tetromino(pieceMan.next());
    moveTimer->restartFallTimer();
}