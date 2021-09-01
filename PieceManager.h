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
	PieceManager()
	{
		srand((unsigned int) time(0));
		init();
	}

	void init()
	{
		bag.clear();
		history.clear();
		hold = 0;
		std::vector<int> tetrominos = {1, 2, 3, 4, 5, 6, 7};
		std::shuffle(tetrominos.begin(), tetrominos.end(), std::default_random_engine((unsigned int) time(0)));
		for(int tetromino : tetrominos)
		{
			bag.push_back(tetromino);
		}
		for(unsigned int i = 3; i < tetrominos.size(); i++)
		{
			history.push_back(tetrominos[i]);
		}
	}

	int getNext()
	{
		int next = bag.front();
		bag.pop_front();
		generateNext();
		return next;
	}

	void swap(Tetromino &tetromino)
	{
		int type = tetromino.getType();
		if(hold == 0)
		{
			tetromino.setType(getNext());
		}
		else
		{
			tetromino.setType(hold);
		}
		hold = type;
	}

private:
	std::deque<int> history;
	std::deque<int> bag;
	int hold;

	void generateNext()
	{
		int tetromino = 0;
		int tries = 0;
		do
		{
			tetromino = rand() % 7 + 1;
			tries++;
		}
		while(std::count(history.begin(), history.end(), tetromino) > 0 && tries < 6);
		bag.push_back(tetromino);
		history.pop_front();
		history.push_back(tetromino);

	}
};