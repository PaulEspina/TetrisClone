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

	void init();
	int next();
	void swap(Tetromino &tetromino);

	const std::deque<int> getBag();
	const std::deque<int> getHistory();

private:
	std::deque<int> history;
	std::deque<int> bag;
	int hold;

	void generateNext();
};