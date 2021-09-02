#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <time.h>

#include "MovementSettings.h"
#include "Well.h"
#include "KeyManager.h"
#include "PieceManager.h"

class Game
{
public:
	Game(MovementSettings &movSettings);

	void init();
	void tick(KeyManager &keyManager);
	void update();
	void render(sf::RenderWindow &window);
private:
	MovementSettings *movSettings;
	PieceManager pieceMan;
	Well well;
	Tetromino currentPiece;

	void dropPiece();
};

