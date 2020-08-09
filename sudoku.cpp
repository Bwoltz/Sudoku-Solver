#include "sudoku.h"

void Sudoku::createPuzzle() //Hardcoded puzzle for testing
{
	//row 1
	puzzle[0][0] = 0;
	puzzle[0][1] = 0;
	puzzle[0][2] = 0;
	puzzle[0][3] = 0;
	puzzle[0][4] = 8;
	puzzle[0][5] = 0;
	puzzle[0][6] = 0;
	puzzle[0][7] = 0;
	puzzle[0][8] = 0;

	//row 2
	puzzle[1][0] = 0;
	puzzle[1][1] = 9;
	puzzle[1][2] = 0;
	puzzle[1][3] = 3;
	puzzle[1][4] = 0;
	puzzle[1][5] = 0;
	puzzle[1][6] = 0;
	puzzle[1][7] = 0;
	puzzle[1][8] = 0;

	//row 3
	puzzle[2][0] = 1;
	puzzle[2][1] = 0;
	puzzle[2][2] = 5;
	puzzle[2][3] = 0;
	puzzle[2][4] = 4;
	puzzle[2][5] = 7;
	puzzle[2][6] = 9;
	puzzle[2][7] = 3;
	puzzle[2][8] = 0;

	//row 4
	puzzle[3][0] = 0;
	puzzle[3][1] = 6;
	puzzle[3][2] = 2;
	puzzle[3][3] = 4;
	puzzle[3][4] = 0;
	puzzle[3][5] = 0;
	puzzle[3][6] = 1;
	puzzle[3][7] = 9;
	puzzle[3][8] = 0;

	//row 5
	puzzle[4][0] = 0;
	puzzle[4][1] = 0;
	puzzle[4][2] = 0;
	puzzle[4][3] = 0;
	puzzle[4][4] = 0;
	puzzle[4][5] = 0;
	puzzle[4][6] = 0;
	puzzle[4][7] = 0;
	puzzle[4][8] = 0;

	//row 6
	puzzle[5][0] = 0;
	puzzle[5][1] = 1;
	puzzle[5][2] = 8;
	puzzle[5][3] = 0;
	puzzle[5][4] = 0;
	puzzle[5][5] = 3;
	puzzle[5][6] = 2;
	puzzle[5][7] = 5;
	puzzle[5][8] = 0;

	//row 7
	puzzle[6][0] = 0;
	puzzle[6][1] = 4;
	puzzle[6][2] = 9;
	puzzle[6][3] = 7;
	puzzle[6][4] = 6;
	puzzle[6][5] = 0;
	puzzle[6][6] = 8;
	puzzle[6][7] = 0;
	puzzle[6][8] = 5;

	//row 8
	puzzle[7][0] = 0;
	puzzle[7][1] = 0;
	puzzle[7][2] = 0;
	puzzle[7][3] = 0;
	puzzle[7][4] = 0;
	puzzle[7][5] = 1;
	puzzle[7][6] = 0;
	puzzle[7][7] = 6;
	puzzle[7][8] = 0;

	//row 9
	puzzle[8][0] = 0;
	puzzle[8][1] = 0;
	puzzle[8][2] = 0;
	puzzle[8][3] = 0;
	puzzle[8][4] = 3;
	puzzle[8][5] = 0;
	puzzle[8][6] = 0;
	puzzle[8][7] = 0;
	puzzle[8][8] = 0;
}

void Sudoku::printPuzzle()
{
	printf("-------------------------------\n");

	for (uint8_t i = 0;i < 9;i++)
	{
		for (uint8_t j = 0;j < 9;j++)
		{
			if ((j % 3) == 0)
				printf("|");

			printf(" %d ", puzzle[i][j]);
		}
		printf("|\n");

		if ((i + 1) % 3 == 0)
			printf("-------------------------------\n");
	}
}

void Sudoku::solve()
{
	while (row < 9)
	{
		//if element is empty
		if (puzzle[row][column] == 0)
		{
			assignNum();

			if (column == 8)//at the end of a row
			{
				row = row + 1;
				column = 0;
			}
			else
			{
				column = column + 1;
			}
		}
		//if the element is not empty and we're at the last column
		//but not the last row
		else if (column == 8)
		{
			row = row + 1;
			column = 0;
		}
		//if we're at an element before the last column
		else
		{
			column = column + 1;
		}
	}

	return;

}//end solve function

void Sudoku::assignNum()
{
	uint8_t posNum;

	if (puzzle[row][column] == 0) //If element is empty
	{
		posNum = 1;
	}
	else //If element already has a value
	{
		posNum = puzzle[row][column];
	}

	//Loop to find possoble number to place
	while (!checkRow(&posNum) || !checkBox(&posNum) || !checkCol(&posNum))
	{
		posNum++;
	}

	if (posNum == 10)//cannot put valid number
	{
		puzzle[row][column] = 0; //leave the element empty
		backtrack(); //backtrack for different combination
	}
	else //can assign a valid number
	{

		puzzle[row][column] = posNum;

		//Create a new Point structure and append to vector
		Point *newPoint = new Point();
		newPoint->column = column;
		newPoint->row = row;

		visited.push_back(newPoint);
	}

	return;
}

//function to backtrack to previous assigned values
void Sudoku::backtrack()
{
	Point *prevPoint = new Point();

	prevPoint = visited.back();
	visited.pop_back();

	row = prevPoint->row;
	column = prevPoint->column;

	assignNum();
}

//Check for row conflict
bool Sudoku::checkRow(uint8_t* posNum)
{
	for (uint8_t i = 0; i < 9; i++)
	{
		if (puzzle[i][column] == *posNum)
			return false;
	}

	return true;
}

//Check for column conflict
bool Sudoku::checkCol(uint8_t* posNum)
{
	for (uint8_t j = 0; j < 9; j++)
	{
		if (puzzle[row][j] == *posNum)
			return false;
	}

	return true;
}

//Check for box conflict
bool Sudoku::checkBox(uint8_t* posNum)
{
	if (row < 3 && column < 3) //in top left box
	{
		for (uint8_t i = 0; i < 3; i++)
		{
			for (uint8_t j = 0; j < 3; j++)
			{
				if (puzzle[i][j] == *posNum)
					return false;
			}
		}
		return true;
	}

	else if (row < 3 && (column > 2 && column < 6)) //in top middle box
	{
		for (uint8_t i = 0; i < 3; i++)
		{
			for (uint8_t j = 3; j < 6; j++)
			{
				if (puzzle[i][j] == *posNum)
					return false;
			}
		}
		return true;
	}

	else if (row < 3 && column > 5) //in top right box
	{
		for (uint8_t i = 0; i < 3; i++)
		{
			for (uint8_t j = 6; j < 9; j++)
			{
				if (puzzle[i][j] == *posNum)
					return false;
			}
		}
		return true;
	}
	else if ((row > 2 && row < 6) && column < 3) //in middle left box
	{
		for (uint8_t i = 3; i < 6; i++)
		{
			for (uint8_t j = 0; j < 3; j++)
			{
				if (puzzle[i][j] == *posNum)
					return false;
			}
		}
		return true;
	}

	else if ((row > 2 && row < 6) && (column < 6 && column > 2)) // in center box
	{
		for (uint8_t i = 3; i < 6; i++)
		{
			for (uint8_t j = 3; j < 6; j++)
			{
				if (puzzle[i][j] == *posNum)
					return false;
			}
		}
		return true;
	}

	else if ((row > 2 && row < 6) && column > 5) //in middle right box
	{
		for (uint8_t i = 3; i < 6; i++)
		{
			for (uint8_t j = 6; j < 9; j++)
			{
				if (puzzle[i][j] == *posNum)
					return false;
			}
		}
		return true;
	}

	else if (row > 5 && column < 3) //in bottom left box
	{
		for (uint8_t i = 6; i < 9; i++)
		{
			for (uint8_t j = 0; j < 3; j++)
			{
				if (puzzle[i][j] == *posNum)
					return false;
			}
		}
		return true;
	}

	else if (row > 5 && (column > 2 && column < 6)) //in bottom middle box
	{
		for (uint8_t i = 6; i < 9; i++)
		{
			for (uint8_t j = 3; j < 6; j++)
			{
				if (puzzle[i][j] == *posNum)
					return false;
			}
		}
		return true;
	}

	else if (row > 5 && column > 5) //in bottom right box
	{
		for (uint8_t i = 6; i < 9; i++)
		{
			for (uint8_t j = 6; j < 9; j++)
			{
				if (puzzle[i][j] == *posNum)
					return false;
			}
		}
		return true;
	}

	else //somehow out of bounds
	{
		printf("ERROR: checkBox: column and row not within bounds");
		return false;
	}
}
