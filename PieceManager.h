#pragma once

#include <queue>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>

#include "Tetromino.h"

class PieceManager
{
public:
	PieceManager();
	PieceManager(int holdAllowedRepeat);

	void init();
	int next();
	void swap(Tetromino &tetromino);
	void resetHoldRepeat();

	const std::deque<int> getBag();
	const std::deque<int> getHistory();
	int getHold();

private:
	std::deque<int> history;
	std::deque<int> bag;
	int hold;
	int holdAllowedRepeat;
	int holdRemainingRepeat;
	void generateNext();
};