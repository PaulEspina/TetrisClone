#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <time.h>

#include "MovementTimer.h"
#include "Bag.h"
#include "Well.h"
#include "KeyManager.h"
#include "PieceManager.h"

class Game
{
public:
	Game(MovementTimer &moveTimer);

	void init();
	void tick(KeyManager &keyManager);
	void update();
	void render(sf::RenderWindow &window);
private:
	MovementTimer *moveTimer;
	PieceManager pieceMan;
	Well well;
	Bag bag;
	PieceBox holdBox;
	Tetromino currentPiece;

	void dropPiece();
};

