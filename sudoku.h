#pragma once
#include <stdio.h>
#include <vector>

struct Point
{
	uint8_t row, column;

	Point()
	{
		row = NULL;
		column = NULL;
	}

	~Point() {}
};

class Sudoku
{
private:
	uint8_t puzzle[9][9];
	std::vector<Point*> visited;

	uint8_t row, column;

public:
	void createPuzzle();
	void printPuzzle();

	void solve();

	bool checkRow(uint8_t*);
	bool checkCol(uint8_t*);
	bool checkBox(uint8_t*);

	void assignNum();

	void backtrack();

	Sudoku()
	{
		row = 0;
		column = 0;
	}

	~Sudoku() {}
};
