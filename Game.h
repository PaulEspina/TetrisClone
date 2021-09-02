#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <time.h>

#include "Well.h"
#include "KeyManager.h"
#include "PieceManager.h"

class Game
{
public:
	Game();

	void tick(KeyManager &keyManager);
	void update();
	void render(sf::RenderWindow &window);
private:
	sf::Clock dropTimer;
	PieceManager pieceMan;
	Well well;
	Tetromino currentPiece;

	void dropPiece();
};

