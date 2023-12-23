#include "stdio.h"

#define ROWS 9
#define COLS 9

typedef int (*Puzzle)[COLS];

Puzzle createPuzzle();
void printPuzzle(Puzzle puzzle);
int isSafe(int row, int col, Puzzle puzzle);
int solveSudoku(int row, int col, Puzzle puzzle);

int main()
{
	Puzzle puzzle;
	puzzle = createPuzzle();
	printPuzzle(puzzle);

	printf("Solved: \n");

	solveSudoku(0, 0, puzzle);

	return 0;
}





Puzzle createPuzzle()
{
	static int array[ROWS][COLS] = {
			{0, 0, 0, 2, 0, 0, 1, 0, 0},
			{2, 0, 8, 0, 0, 0, 0, 3, 0},
			{7, 3, 0, 0, 8, 9, 0, 0, 0},

			{0, 0, 0, 8, 0, 4, 6, 9, 0},
			{0, 7, 0, 0, 0, 0, 0, 8, 0},
			{0, 0, 6, 0, 2, 1, 3, 0, 0},

			{8, 0, 4, 9, 1, 5, 0, 6, 3},
			{0, 9, 0, 0, 0, 0, 0, 1, 4},
			{6, 1, 7, 3, 0, 8, 0, 5, 2}};

	return array;
}

void printPuzzle(Puzzle puzzle)
{
	int i, j;

	printf("-------------------------------\n");
	for (i = 0; i < ROWS; i++)
	{
		/* print '|' before each row */
		printf("|");

		/* print each row */
		for (j = 0; j < COLS; j++)
		{
			printf(" %d ", puzzle[i][j]);

			if ((j + 1) % 3 == 0)
			{
				printf("|");
			}
		}
		/* print newline after each row */
		printf("\n");

		if ((i + 1) % 3 == 0)
		{
			printf("-------------------------------\n");
		}
	}
}

int isSafe(int row, int col, Puzzle puzzle)
{
	int i, j;
	int elem = puzzle[row][col];

	/* Check all rows in `col` for collision */
	for (i = 0; i < ROWS; i++)
	{
		if (puzzle[i][col] == elem && i != row)
		{
			return 0;
		}
	}

	/* Check all columns in `row` for collision */
	for (j = 0; j < COLS; j++)
	{
		if (puzzle[row][j] == elem && j != col)
		{
			return 0;
		}
	}

	/* Check for collision in 3x3 grid */
	for (i = (row / 3) * 3; i < (row / 3) * 3 + 3; i++)
	{
		for (j = (col / 3) * 3; j < (col / 3) * 3 + 3; j++)
		{
			if (puzzle[i][j] == elem && row != i && col != j)
			{
				return 0;
			}
		}
	}

	return 1;
}

int solveSudoku(int row, int col, Puzzle puzzle)
{

	int i;

	/* if `col` is out of bounds move to next row */
	if (col >= COLS)
	{
		row++;
		col = 0;
	}

	/* if `row` is out of bounds we have solved the puzzle */
	if (row >= ROWS)
	{
		printPuzzle(puzzle);

		return 1;
	}

	/* if the cell already has a number, increment the column and continue */
	if (puzzle[row][col] != 0)
	{
		return solveSudoku(row, col + 1, puzzle);
	}

	/* try each integer from 1 to 9 sequentially */
	for (i = 1; i <= 9; i++)
	{
		puzzle[row][col] = i;

		if (isSafe(row, col, puzzle))
		{
			/* If the assigned number is safe for the cell, continue solving */
			if (solveSudoku(row, col + 1, puzzle))
			{
				return 1;
			}
		}

		/* reset the value when backtracking */
		puzzle[row][col] = 0;
	}

	return 0;
}
