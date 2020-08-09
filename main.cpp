#include "sudoku.h"

int main()
{
	Sudoku s;

	s.createPuzzle();
	s.printPuzzle();

	s.solve();

	s.printPuzzle();

	printf("Press ENTER to exit.\n");
	getchar();
}
