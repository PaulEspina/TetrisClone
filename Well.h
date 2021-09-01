#pragma once

#include <SFML/Graphics.hpp>
#include "Tetromino.h"
#include <vector>
#include <stack>

class Well
{
public:
    Well();
    Well(sf::Vector2f pos, sf::Vector2u dimension = sf::Vector2u(10, 20), unsigned int extraBlocks = 3, unsigned int blockSize = 25);

    void init();
    void update();
    void render(sf::RenderWindow *window);
    void showCurrentPiece(Tetromino tetromino);
    void previewDrop(Tetromino tetromino);
    void placePiece(Tetromino tetromino);
    void dropCurrentPiece();
    bool inBounds(Tetromino tetromino);
    void findValidGrid(Tetromino &tetromino);

private:
    unsigned int extraBlocks;
    unsigned int wellWidth;
    unsigned int wellHeight;
    unsigned int trueWellHeight;
    unsigned int blockSize;

    std::vector<std::vector<char>> well;
    std::vector<std::vector<char>> newWell;
    std::vector<sf::RectangleShape> blockRects;
    sf::RectangleShape wellRect;
    sf::Vector2f pos;

    unsigned int occupiedHeight;

    Tetromino currentPiece;
    Tetromino previewPiece;
};