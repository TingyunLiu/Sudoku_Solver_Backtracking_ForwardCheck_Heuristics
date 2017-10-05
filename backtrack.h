#include <iostream>

// Macros for the program
#define GRID_SIZE 9
#define SUBGRID_SIZE 3
#define MAX_NUMBER_ASSIGNMENT_ALLOWED 10000


//********************************************************************************************************************
// This class is standard Backtracking search only
// Base class for class BacktrackForwardcheck
//********************************************************************************************************************
class Backtrack {
protected:
	int total_number_of_assignment;	// keep track of number of variable assignment
	int grid[GRID_SIZE][GRID_SIZE]; // keep the sudoku grid
	bool find_next_available(int &row, int &column); // get the next available assigned cell and pass to row, column
	bool check_same_row(int row, int value); // check if there is a value existing in the same row
	bool check_same_column(int column, int value); // check if there is a value existing in the same column
	bool check_same_subgrid(int row, int column, int value); // check if there is a value existing in the same subgrid
	bool check_availability(int row, int column, int value); // check if the value can be assigned in the position 
	virtual bool cause_unsolvable(); // check if there is a cell has no value can be assigned to, which is unsolvable
public:
	Backtrack(int grid[][GRID_SIZE]); // constructor, set up the grid in the class
	virtual bool solve(); // function to solve the the sudoku
	void print_grid(); // print the final states of the sudoku
};


