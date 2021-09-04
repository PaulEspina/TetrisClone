#pragma once

#include <string>
#include <SFML/System.hpp>
#include <vector>

class Tetromino
{
public:
    Tetromino();
    Tetromino(unsigned int type);
    Tetromino(sf::Vector2i gridPos, unsigned int type);
    
    void rotateClockwise();
    void rotateCounterClockwise();
    void move(sf::Vector2i distance);

    void setType(int type);
    unsigned int getType();
    const std::vector<std::vector<char>> getShape();
    void setGridPos(sf::Vector2i gridPos);
    sf::Vector2i getGridPos();
    bool isAtBottom();
    void setAtBottom(bool value);
    bool shouldLock();
    void setDropLock(bool value);
private:
    std::vector<std::vector<char>> shape;
    unsigned int type;
    sf::Vector2i gridPos;
    bool atBottom;
    bool dropLock;
};